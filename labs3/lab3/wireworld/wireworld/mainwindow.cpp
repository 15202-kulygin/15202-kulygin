#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(overflowedTime()));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}




void MainWindow::on_Step_clicked()
{
    ui->widget->makeStep();
}

void MainWindow::on_NSteps_clicked()
{
    bool ok;
    int N = QInputDialog::getInt(this, tr("Make N steps"), tr("Enter the number of steps (Default = 10, Min = 0, Max = 1000) :"), 10, 0, 1000, 1, &ok);
    if (ok)
    {
       for (int i = 0; i < N; ++i)
       {
            ui->widget->makeStep();
       }
    }
}

 void MainWindow::overflowedTime()
 {
     ui->widget->makeStep();
     timer->start(500);
 }

void MainWindow::on_Start_clicked()
{
    timer->start(500);
}

void MainWindow::on_Stop_clicked()
{
    timer->stop();
}

void MainWindow::on_Clear_clicked()
{
    ui->widget->clearField();
}
