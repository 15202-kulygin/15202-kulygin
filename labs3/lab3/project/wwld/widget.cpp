#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            delete field[i][j];
        }
    }
    delete timer;
    delete scene;
    delete ui;
}

Widget::Widget(int x, int y) :
    x(x), y(y), iterations(0), scene(nullptr), QWidget(0), ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(100);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout));

    //timer start

}

void Widget::new_game()
{
    if (scene == nullptr) {
        scene = new QGraphicsScene(0,0,ui->graphicsView->viewport()->width(),ui->graphicsView->viewport()->height());
        field.resize(x);
        for (int i = 0; i < x; i++){
            field[i].resize(y);
            for (int j = 0; j < y; j++)
            {
                Cell * cell1 = new Cell(0,0,scene->sceneRect().width()/(x),scene->sceneRect().height()/(y));
                scene->addItem(cell1);
                cell1->setPos(0 + i*scene->width()/(x), 0 + j*scene->height()/(y) );
                field[i][j] = cell1;
            }
        }
    }
    else
    {
        timer->stop();
        iterations = 0;
        for (int i = 0; i < x; i++){

            for (int j = 0; j < y; j++)
            {
                field[i][j]->setBrush(QBrush(Qt::gray));
            }
        }
    }
    ui->graphicsView->setScene(scene);

}

void Widget::on_pushButton_clicked()
{
     new_game();
}

void Widget::on_pushButton_2_clicked()
{
    if (scene != nullptr)
    {
        timer->start();
    }
}


