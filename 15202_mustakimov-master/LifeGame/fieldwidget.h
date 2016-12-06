#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPoint>
#include "field.h"

class FieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldWidget(QWidget * parent = 0);

    int getFieldWidth(){return field->getWidth();}
    int getFieldHeight(){return field->getHeight();}

    void resizeField(int width, int height);

protected:
    void paintEvent(QPaintEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

signals:

public slots:
    void stepOnce() { field->step(1); repaint(); }
    void stepN(int N) { field->step(N); repaint(); }
    void zoomIn() { cellSize *= 1.3; repaint(); }
    void zoomOut() { cellSize /= 1.3; repaint(); }
    void clearField() { field->clearField(); repaint(); }
    void randomizeField() { field->randomizeField(); repaint(); }

private:
    QPoint mousePosition;
    QPoint previousMousePosition;

    int cellSize = 25;

    QPoint cellOffset;

    Field * field;

    QPoint screenToWorld(QPoint) const;

    void DrawCells(QPainter &p);
    void DrawGrid(QPainter & p, QPen pen);
    void DrawBorder(QPainter & p);
};

#endif // FIELDWIDGET_H
