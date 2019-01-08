/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *RUN;
    QLabel *optic_window;
    QLabel *IR_window;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1515, 546);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        RUN = new QPushButton(centralwidget);
        RUN->setObjectName(QStringLiteral("RUN"));
        RUN->setGeometry(QRect(10, 10, 111, 51));
        optic_window = new QLabel(centralwidget);
        optic_window->setObjectName(QStringLiteral("optic_window"));
        optic_window->setGeometry(QRect(130, 10, 640, 480));
        IR_window = new QLabel(centralwidget);
        IR_window->setObjectName(QStringLiteral("IR_window"));
        IR_window->setGeometry(QRect(840, 10, 640, 480));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1515, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        RUN->setText(QApplication::translate("MainWindow", "RUN", Q_NULLPTR));
        optic_window->setText(QString());
        IR_window->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
