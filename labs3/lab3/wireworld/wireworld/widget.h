#ifndef WIDGET_H
#define WIDGET_H

#include<memory>
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
    void resizeField(int h, int w);

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
    std::unique_ptr<Field> field;
    std::unique_ptr<Field> buffer;
    std::unique_ptr<Ui::Widget> ui;
};

#endif // WIDGET_H
