#include <QInputDialog>
#include <QTimer>
#include <fstream>
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
       timer->stop();
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
        std::ofstream file;
        file.open(str);
        int fieldHeight = ui->widget->get_field()->getHeight();
        int fieldWidth = ui->widget->get_field()->getWidth();
        file << "x = " << fieldHeight << ", y = " << fieldWidth << ", rule = WireWorld" << std::endl;
        for (int i = 0; i < fieldHeight; ++i)
        {
            for (int j = 0; j < fieldWidth; ++j)
            {
                Cell to_get = ui->widget->get_field()->getCell(i, j);
                if (EMPTY == to_get)
                {
                    file << ".";
                }
                else if (TAIL == to_get)
                {
                    file << "T";
                }
                if (CONDUCTOR == to_get)
                {
                    file << "C";
                }
                if (HEAD == to_get)
                {
                    file << "A";
                }
            }
            file << "$" << std::endl;
        }
        file << "!";
        file.close();
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
        std::string strg = text.toLocal8Bit().constData();
        std::ifstream file;
        file.open(strg);
        if (!file.is_open())
        {
            return;
        }
        char x;
        std::string str;
        int fieldHeight;
        int fieldWidth;
        file >> x >> x >> fieldHeight >> x >> x >> x >> fieldWidth >> x >> str >> str >> str;
        ui->widget->resizeField(fieldHeight, fieldWidth);
        for (int i = 0; i < fieldHeight; ++i)
        {
            for (int j = 0; j < fieldWidth; ++j)
            {
                file >> x;
                if ('.' == x)
                {
                    ui->widget->get_field()->changeCell(i, j, EMPTY);
                }
                else if ('A' == x)
                {
                    ui->widget->get_field()->changeCell(i, j, HEAD);
                }
                else if ('T' == x)
                {
                    ui->widget->get_field()->changeCell(i, j, TAIL);
                }
                else if ('C' == x)
                {
                    ui->widget->get_field()->changeCell(i, j, CONDUCTOR);
                }
            }
            file >> x;
        }
        file.close();
        ui->widget->update();
    }
}

