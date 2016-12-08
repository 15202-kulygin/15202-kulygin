#include <QPainter>
#include <QtGui/QMouseEvent>
#include "widget.h"
#include "ui_widget.h"

const QColor Widget::GRIDCOLOR = Qt::black;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    field = new Field;
    buffer = new Field;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete field;
    delete buffer;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    paintField(p);
    paintGrid(p);
}

void Widget::paintGrid(QPainter &p)
{
    p.setPen(GRIDCOLOR);
    int FieldWidth = field->getWidth();
    int FieldHeight = field->getHeight();
    for(int i = 0; i <= FieldWidth; i++)
        p.drawLine(i * CELLSIZE, 0, i * CELLSIZE, FieldHeight * CELLSIZE);
    for(int i = 0; i <= FieldHeight; i++)
        p.drawLine(0, i * CELLSIZE, FieldWidth * CELLSIZE, i * CELLSIZE);
}

void Widget::paintField(QPainter &p)
{
    int FieldWidth = field->getWidth();
    int FieldHeight = field->getHeight();
    for(int i = 0; i < FieldHeight; i++)
    {
        for(int j = 0; j < FieldWidth; j++)
        {
            qreal left = (qreal)(CELLSIZE * j);
            qreal top  = (qreal)(CELLSIZE * i);
            QRectF rect(left, top, (qreal)CELLSIZE, (qreal)CELLSIZE);
            QColor CellColor;
            Cell to_get = field->getCell(i, j);
            if (EMPTY == to_get)
            {
                CellColor = Qt::darkGray;
            }
            else if (TAIL == to_get)
            {
                CellColor = Qt::blue;
            }
            if (CONDUCTOR == to_get)
            {
                CellColor = Qt::yellow;
            }
            if (HEAD == to_get)
            {
                CellColor = Qt::red;
            }
            p.fillRect(rect, QBrush(CellColor));
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
   if ((event->y() >= CELLSIZE * field->getHeight()) || (event->x() >= CELLSIZE * field->getWidth()))
       return;
   double cellHeight = event->y() / CELLSIZE;
   double cellWidth = event->x() / CELLSIZE;
   field->changeCell((int)cellHeight, (int)cellWidth);
   buffer->changeCell((int)cellHeight, (int)cellWidth);
   update();
}

void Widget::makeStep()
{
    int fieldHeight = field->getHeight();
    int fieldWidth = field->getWidth();
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            if (EMPTY == buffer->getCell(i, j))
            {
                field->changeCell(i, j, EMPTY);
            }
            else if (HEAD == buffer->getCell(i, j))
            {
                field->changeCell(i, j, TAIL);
            }
            if (TAIL == buffer->getCell(i, j))
            {
                field->changeCell(i, j, CONDUCTOR);
            }
            if (CONDUCTOR == buffer->getCell(i, j))
            {
                if ((2 == buffer->countHeads(i, j)) || (1 == buffer->countHeads(i, j)))
                {
                    field->changeCell(i, j, HEAD);
                }
            }
        }
    }
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            buffer->changeCell(i, j, field->getCell(i, j));
        }
    }
    update();
}

void Widget::clearField()
{
    delete field;
    delete buffer;
    field = new Field;
    buffer = new Field;
    update();
}




