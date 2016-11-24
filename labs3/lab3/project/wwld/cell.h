#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QtWidgets>

class Cell : public QGraphicsRectItem
{
public:
    Cell();
    Cell(qreal x, qreal y, qreal w, qreal h, QGraphicsItem * parent = 0);
    ~Cell();
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void click_changeColor();
    void changeColor();
};

#endif // CELL_H
