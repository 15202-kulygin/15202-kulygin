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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "fieldwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStep;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionN_Steps;
    QAction *actionResize;
    QAction *actionClear;
    QAction *actionRandomize;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    FieldWidget *fieldWidget;
    QMenuBar *menubar;
    QMenu *menuSimulation;
    QMenu *menuView;
    QMenu *menuField;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionStep = new QAction(MainWindow);
        actionStep->setObjectName(QStringLiteral("actionStep"));
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionN_Steps = new QAction(MainWindow);
        actionN_Steps->setObjectName(QStringLiteral("actionN_Steps"));
        actionResize = new QAction(MainWindow);
        actionResize->setObjectName(QStringLiteral("actionResize"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionRandomize = new QAction(MainWindow);
        actionRandomize->setObjectName(QStringLiteral("actionRandomize"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fieldWidget = new FieldWidget(centralwidget);
        fieldWidget->setObjectName(QStringLiteral("fieldWidget"));

        verticalLayout->addWidget(fieldWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuSimulation = new QMenu(menubar);
        menuSimulation->setObjectName(QStringLiteral("menuSimulation"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuField = new QMenu(menubar);
        menuField->setObjectName(QStringLiteral("menuField"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuField->menuAction());
        menubar->addAction(menuSimulation->menuAction());
        menubar->addAction(menuView->menuAction());
        menuSimulation->addAction(actionStep);
        menuSimulation->addAction(actionN_Steps);
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_Out);
        menuField->addAction(actionResize);
        menuField->addSeparator();
        menuField->addAction(actionClear);
        menuField->addAction(actionRandomize);

        retranslateUi(MainWindow);
        QObject::connect(actionStep, SIGNAL(triggered()), fieldWidget, SLOT(stepOnce()));
        QObject::connect(actionZoom_In, SIGNAL(triggered()), fieldWidget, SLOT(zoomIn()));
        QObject::connect(actionZoom_Out, SIGNAL(triggered()), fieldWidget, SLOT(zoomOut()));
        QObject::connect(actionN_Steps, SIGNAL(triggered()), MainWindow, SLOT(stepNClicked()));
        QObject::connect(actionResize, SIGNAL(triggered()), MainWindow, SLOT(resizeFieldClicked()));
        QObject::connect(actionRandomize, SIGNAL(triggered()), fieldWidget, SLOT(randomizeField()));
        QObject::connect(actionClear, SIGNAL(triggered()), fieldWidget, SLOT(clearField()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStep->setText(QApplication::translate("MainWindow", "Step", 0));
        actionStep->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom In", 0));
        actionZoom_In->setShortcut(QApplication::translate("MainWindow", "Ctrl+=", 0));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom Out", 0));
        actionZoom_Out->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0));
        actionN_Steps->setText(QApplication::translate("MainWindow", "N Steps...", 0));
        actionN_Steps->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+R", 0));
        actionResize->setText(QApplication::translate("MainWindow", "Resize...", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        actionRandomize->setText(QApplication::translate("MainWindow", "Randomize", 0));
        menuSimulation->setTitle(QApplication::translate("MainWindow", "Simulation", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuField->setTitle(QApplication::translate("MainWindow", "Field", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
