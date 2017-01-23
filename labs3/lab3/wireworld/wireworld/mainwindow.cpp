#include <QInputDialog>
#include <QTimer>
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
     timer->start(interval_size);
 }

void MainWindow::on_Start_clicked()
{
    timer->start(interval_size);
}

void MainWindow::on_Stop_clicked()
{
    timer->stop();
}

void MainWindow::on_Clear_clicked()
{
    ui->widget->clearField();
}

void MainWindow::on_ChangeInterval_clicked()
{
    bool ok;
    int N = QInputDialog::getInt(this, tr("Change interval"), tr("Enter the interval value, ms (Default = 500, Min = 0, Max = 5000) :"), 500, 0, 5000, 1, &ok);
    if (ok)
    {
        interval_size = N;
    }
}

void MainWindow::on_ResizeField_clicked()
{
    bool ok1;
    bool ok2;
    int N = QInputDialog::getInt(this, tr("Resize field"), tr("Enter new height (Default = 20, Min = 0, Max = 45) :"), 20, 0, 45, 1, &ok1);
    int M = QInputDialog::getInt(this, tr("Resize field"), tr("Enter new width (Default = 20, Min = 0, Max = 85) :"), 20, 0, 85, 1, &ok2);
    if (ok1 && ok2)
    {
       ui->widget->resizeField(N, M);
    }
}

void MainWindow::on_SaveToFile_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(
                          this,
                          tr("Save to file"),
                          tr("Enter file name:"),
                          QLineEdit::Normal,
                          tr("result.txt"),
                          &ok );
    if( ok && !text.isEmpty() )
    {
        timer->stop();
        std::string str = text.toLocal8Bit().constData();
        ui->widget->saveToFile(str);
        //timer->start(interval_size);
    }
}

void MainWindow::on_LoadFromFile_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(
                          this,
                          tr("Save to file"),
                          tr("Enter file name:"),
                          QLineEdit::Normal,
                          tr("result.txt"),
                          &ok );
    if( ok && !text.isEmpty() )
    {
        timer->stop();
        std::string str = text.toLocal8Bit().constData();
        ui->widget->loadFromFile(str);
    }
}
