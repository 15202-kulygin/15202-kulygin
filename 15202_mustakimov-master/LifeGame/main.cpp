#include <QApplication>
#include <QtGui>
#include <QVBoxLayout>
#include <QPushButton>

#include "fieldwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
