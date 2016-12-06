#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void stepNClicked();
    void resizeFieldClicked();

private:
    Ui::MainWindow *ui;

    int previousNStepsCount = 5;
};

#endif // MAINWINDOW_H
