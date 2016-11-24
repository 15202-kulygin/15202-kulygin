#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <cell.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(int x, int y);
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    int x;
    int y;
    int iterations;
    QVector<QVector<Cell *>> field;
    QGraphicsScene * scene;
    QTimer * timer;

    void new_game();
};

#endif // WIDGET_H
