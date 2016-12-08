#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QColor>
#include "field.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void clearField();
public slots:
    void makeStep();


protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void paintGrid(QPainter &p);
    void paintField(QPainter &p);


    static const int CELLSIZE = 20;
    static const QColor GRIDCOLOR;
    Field * field;
    Field * buffer;
    Ui::Widget *ui;
};

#endif // WIDGET_H
