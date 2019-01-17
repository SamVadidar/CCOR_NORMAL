#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RUN_clicked()
{
    optic = cv::imread("/home/sam/Dev/qt/normalizedxcorrelation/optic.png");
    facemark = cv::face::FacemarkLBF::create();
    facemark->loadModel("/home/sam/Downloads/asd/OpenCV-CPP-show-webcam-stream-on-Qt-GUI-master/OpenCV-CPP-show-webcam-stream-on-Qt-GUI-master/lbfmodel.yaml");

    if (optic.empty())
    {
        std::cout << " optic is empty" << std::endl;
    }
    else
    {
        faceDetector = new cv::CascadeClassifier("/home/sam/Downloads/asd/OpenCV-CPP-show-webcam-stream-on-Qt-GUI-master/OpenCV-CPP-show-webcam-stream-on-Qt-GUI-master/haarcascade_frontalface_alt2.xml");
        faceDetector->detectMultiScale(optic, faces);
        success = facemark->fit(optic, faces, landmarks);
        if (success)
        {
            for(int i = 0; i <landmarks.size(); i++)
            {
                drawLandmarks(optic, landmarks[i]);
            }
        }
    }

//  cv::resize(optic, optic, cv::Size(640, 480)); // size input is (column, row)
    cv::cvtColor(optic, optic, CV_BGR2GRAY);
    cv::GaussianBlur(optic, optic, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

    cv::Sobel(optic, optic_grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(optic, optic_grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

    // converting back to CV_8U
    cv::convertScaleAbs(optic_grad_x, optic_abs_grad_x);
    cv::convertScaleAbs(optic_grad_y, optic_abs_grad_y);
    cv::addWeighted(optic_abs_grad_x, 0.5, optic_abs_grad_y, 0.5, 0, optic_grad);

    qt_optic = QImage((const unsigned char*) (optic_grad.data), optic_grad.cols, optic_grad.rows, QImage::Format_Grayscale8);

    ui->optic_window->setPixmap(QPixmap::fromImage(qt_optic));
    ui->optic_window->resize(ui->optic_window->pixmap()->size());

    //**********************IR

    IR = cv::imread("/home/sam/Dev/qt/normalizedxcorrelation/rgb7.png");
    if (IR.empty())
    {
        std::cout << " IR is empty" << std::endl;
    }

   cv::resize(IR, IR, cv::Size(640, 480));
   cv::cvtColor(IR, IR, CV_BGR2GRAY);
   cv::GaussianBlur(IR, IR, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

   cv::Sobel(IR, IR_grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
   cv::Sobel(IR, IR_grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

   // converting back to CV_8U
   cv::convertScaleAbs(IR_grad_x, IR_abs_grad_x);
   cv::convertScaleAbs(IR_grad_y, IR_abs_grad_y);
   cv::addWeighted(IR_abs_grad_x, 0.5, IR_abs_grad_y, 0.5, 0, IR_grad);

   // resize just to optic size cv::Size(col, row)
   //cv::resize(IR_grad, IR_grad, cv::Size(640, 480));
   //Note that Qimage format is (col, row) and OpenCV is (row, col)
//   qt_IR = QImage((const unsigned char*) (IR_grad.data), IR_grad.cols, IR_grad.rows, QImage::Format_Grayscale8);
//   ui->IR_window->setPixmap(QPixmap::fromImage(qt_IR));
//   ui->IR_window->resize(ui->IR_window->pixmap()->size());

   for(i=0.7; i<1.01; i= i+0.01)
   {
       // resize to find the scalling factor
       // Make sure that in this step IR frame has the same size of the optic one!
       IR_cols = IR_grad.cols * i;
       IR_rows = IR_grad.rows * i;
       cv::resize(IR_grad, temp, cv::Size(IR_cols, IR_rows ));

       // sliding template - result of each step
//       result_cols =  optic.cols - temp.cols + 1;
//       result_rows = optic.rows - temp.rows + 1;
//       result.create( result_rows, result_cols, CV_32FC1 );

       cv::matchTemplate(optic_grad, temp, result, cv::TM_CCORR_NORMED, cv::noArray());

       cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

       if(maxVal > matchVal)
       {
          matchVal = maxVal;
          matchLoc = maxLoc;
          // the highest matchVal refers to the best scale factor
          scale_factor = i;
       }
   }
   std::cout <<  "Scale Factor: " << scale_factor << std::endl;
   std::cout << "X_offset: " << matchLoc.x << std::endl;
   std::cout << "Y_offset: " << matchLoc.y << std::endl;

   x_optic_nose = landmarks[0][30].x;
   y_optic_nose = landmarks[0][30].y;
   x_IR_nose = int ((x_optic_nose - matchLoc.x)/ scale_factor);
   y_IR_nose = int ((y_optic_nose - matchLoc.y)/ scale_factor);

   cv::circle(IR_grad, cv::Point(x_IR_nose, y_IR_nose), 2, COLOR, cv::FILLED);
   qt_IR = QImage((const unsigned char*) (IR_grad.data), IR_grad.cols, IR_grad.rows, QImage::Format_Grayscale8);
   ui->IR_window->setPixmap(QPixmap::fromImage(qt_IR));
   ui->IR_window->resize(ui->IR_window->pixmap()->size());
}

void MainWindow::drawLandmarks(cv::Mat &im, std::vector<cv::Point2f> &landmarks)
{
    for(int i = 0; i < landmarks.size(); i++)
    {
      cv::circle(im,landmarks[i],1, COLOR, cv::FILLED);
     // std::cout << "(Point" <<i+1<<":)" <<landmarks[i] << std::endl;
    }
}
