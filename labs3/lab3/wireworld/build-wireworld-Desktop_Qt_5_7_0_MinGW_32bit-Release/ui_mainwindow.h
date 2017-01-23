/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "widget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    Widget *widget;
    QPushButton *Step;
    QPushButton *NSteps;
    QPushButton *Start;
    QPushButton *Stop;
    QPushButton *Clear;
    QPushButton *ChangeInterval;
    QPushButton *ResizeField;
    QPushButton *SaveToFile;
    QPushButton *LoadFromFile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(734, 694);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new Widget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(110, 10, 1791, 1001));
        widget->setMaximumSize(QSize(1791, 1001));
        Step = new QPushButton(centralWidget);
        Step->setObjectName(QStringLiteral("Step"));
        Step->setGeometry(QRect(10, 10, 91, 23));
        NSteps = new QPushButton(centralWidget);
        NSteps->setObjectName(QStringLiteral("NSteps"));
        NSteps->setGeometry(QRect(10, 40, 91, 23));
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QStringLiteral("Start"));
        Start->setGeometry(QRect(10, 70, 91, 23));
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setGeometry(QRect(10, 100, 91, 23));
        Clear = new QPushButton(centralWidget);
        Clear->setObjectName(QStringLiteral("Clear"));
        Clear->setGeometry(QRect(10, 130, 91, 23));
        ChangeInterval = new QPushButton(centralWidget);
        ChangeInterval->setObjectName(QStringLiteral("ChangeInterval"));
        ChangeInterval->setGeometry(QRect(10, 160, 91, 23));
        ResizeField = new QPushButton(centralWidget);
        ResizeField->setObjectName(QStringLiteral("ResizeField"));
        ResizeField->setGeometry(QRect(10, 190, 91, 23));
        SaveToFile = new QPushButton(centralWidget);
        SaveToFile->setObjectName(QStringLiteral("SaveToFile"));
        SaveToFile->setGeometry(QRect(10, 220, 91, 23));
        LoadFromFile = new QPushButton(centralWidget);
        LoadFromFile->setObjectName(QStringLiteral("LoadFromFile"));
        LoadFromFile->setGeometry(QRect(10, 250, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 734, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Step->setText(QApplication::translate("MainWindow", "Step", 0));
        NSteps->setText(QApplication::translate("MainWindow", "N Steps", 0));
        Start->setText(QApplication::translate("MainWindow", "Start", 0));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0));
        Clear->setText(QApplication::translate("MainWindow", "Clear", 0));
        ChangeInterval->setText(QApplication::translate("MainWindow", "Change interval", 0));
        ResizeField->setText(QApplication::translate("MainWindow", "Resize field", 0));
        SaveToFile->setText(QApplication::translate("MainWindow", "Save to file", 0));
        LoadFromFile->setText(QApplication::translate("MainWindow", "Load from file", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
