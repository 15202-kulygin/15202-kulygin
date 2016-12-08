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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *gameLayout;
    QVBoxLayout *setLayout;
    QHBoxLayout *controlLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *clearButton;
    QLabel *label;
    QSpinBox *cellsControl;
    QLabel *label2;
    QSpinBox *iterInterval;
    QHBoxLayout *fileLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *colorButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        gameLayout = new QVBoxLayout();
        gameLayout->setSpacing(6);
        gameLayout->setObjectName(QStringLiteral("gameLayout"));

        mainLayout->addLayout(gameLayout);

        setLayout = new QVBoxLayout();
        setLayout->setSpacing(6);
        setLayout->setObjectName(QStringLiteral("setLayout"));
        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(6);
        controlLayout->setObjectName(QStringLiteral("controlLayout"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        controlLayout->addWidget(startButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        controlLayout->addWidget(stopButton);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        controlLayout->addWidget(clearButton);


        setLayout->addLayout(controlLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        setLayout->addWidget(label);

        cellsControl = new QSpinBox(centralWidget);
        cellsControl->setObjectName(QStringLiteral("cellsControl"));
        cellsControl->setMinimum(10);
        cellsControl->setMaximum(400);
        cellsControl->setValue(50);

        setLayout->addWidget(cellsControl);

        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));

        setLayout->addWidget(label2);

        iterInterval = new QSpinBox(centralWidget);
        iterInterval->setObjectName(QStringLiteral("iterInterval"));
        iterInterval->setMinimum(50);
        iterInterval->setMaximum(100000);
        iterInterval->setSingleStep(10);
        iterInterval->setValue(100);

        setLayout->addWidget(iterInterval);

        fileLayout = new QHBoxLayout();
        fileLayout->setSpacing(6);
        fileLayout->setObjectName(QStringLiteral("fileLayout"));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QStringLiteral("loadButton"));

        fileLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        fileLayout->addWidget(saveButton);


        setLayout->addLayout(fileLayout);

        colorButton = new QPushButton(centralWidget);
        colorButton->setObjectName(QStringLiteral("colorButton"));

        setLayout->addWidget(colorButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        setLayout->addItem(verticalSpacer);


        mainLayout->addLayout(setLayout);


        horizontalLayout->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Conway's Game of Life", 0));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        label->setText(QApplication::translate("MainWindow", "Universe Size", 0));
        cellsControl->setSuffix(QApplication::translate("MainWindow", " cells", 0));
        label2->setText(QApplication::translate("MainWindow", "Generation interval (in msec)", 0));
        iterInterval->setSuffix(QApplication::translate("MainWindow", " ms", 0));
        loadButton->setText(QApplication::translate("MainWindow", "Load", 0));
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
        colorButton->setText(QApplication::translate("MainWindow", "Select color for cells", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
