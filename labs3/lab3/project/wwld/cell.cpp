#include "cell.h"

Cell::Cell()
{
    this->setBrush(QBrush(Qt::gray));
}

Cell::Cell(qreal x, qreal y, qreal w, qreal h, QGraphicsItem * parent):
    QGraphicsRectItem(x, y, w, h, parent)
{
    this->setBrush(QBrush(Qt::gray));
}

Cell::~Cell()
{

}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    click_changeColor();
}

void Cell::click_changeColor()
{
    if (this->brush().color() == Qt::gray)
    {
        this->setBrush((QBrush(Qt::yellow)));
    }
    else if (this->brush().color() == Qt::yellow)
    {
        this->setBrush((QBrush(Qt::blue)));
    }
    else if (this->brush().color() == Qt::blue)
    {
        this->setBrush((QBrush(Qt::red)));
    }
    else
    {
        this->setBrush((QBrush(Qt::gray)));
    }
}

void Cell::changeColor()
{

}
