#include "fieldwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>

#include <iostream>

FieldWidget::FieldWidget(QWidget * parent) : QWidget(parent)
{
    field = new Field();
}

void FieldWidget::resizeField(int width, int height)
{
    delete field;
    field = new Field(width, height);

    repaint();
}

void FieldWidget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);

    QPen gridPen;
    if (cellSize <= 10)
    {
        gridPen = QPen(Qt::black, 0, Qt::NoPen);
    }
    else if (cellSize <= 20)
    {
        gridPen = QPen(Qt::black, 1, Qt::SolidLine);
    }
    else
    {
        gridPen = QPen(Qt::black, 2, Qt::SolidLine);
        // For lines to hit pixels when antialiasing:
        //p.translate(0.5,0.5);
        p.setRenderHint(QPainter::Antialiasing);
    }

    p.translate(cellOffset);

    DrawCells(p);
    DrawGrid(p, gridPen);
    DrawBorder(p);
}

void FieldWidget::DrawCells(QPainter & p)
{
    QPen myPen(Qt::darkGray, 0, Qt::NoPen);
    p.setPen(myPen);
    QBrush myBrush(Qt::darkGray);
    p.setBrush(myBrush);

    for (int x = 0; x < field->getWidth(); ++x)
    {
        for (int y = 0; y < field->getHeight(); ++y)
        {
            if (field->getCell(x, y))
            {
                QRectF cell(x * cellSize,
                            y * cellSize,
                            cellSize, cellSize);
                p.drawRect(cell);
            }
        }
    }
}

void FieldWidget::DrawGrid(QPainter & p, QPen pen)
{
    p.setPen(pen);

    int fieldWidth = field->getWidth() * cellSize;
    int fieldHeight = field->getHeight() * cellSize;

    for (int x = 0; x < field->getWidth() + 1; ++x)
    {
        QLineF line(x * cellSize,
                    0,
                    x * cellSize,
                    fieldHeight);
        p.drawLine(line);
    }

    for (int y = 0; y < field->getHeight() + 1; ++y)
    {
        QLineF line(0,
                    y * cellSize,
                    fieldWidth,
                    y * cellSize);
        p.drawLine(line);
    }
}

void FieldWidget::DrawBorder(QPainter &p)
{
    int fieldWidth = field->getWidth() * cellSize;
    int fieldHeight = field->getHeight() * cellSize;

    QPen myPen(Qt::red, 4, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(myPen);
    QBrush myBrush(Qt::NoBrush);
    p.setBrush(myBrush);

    p.drawRect(-5, -5, fieldWidth+10, fieldHeight+10);
}

void FieldWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    cellOffset += mousePosition - previousMousePosition;

    previousMousePosition = mousePosition;

    repaint();
}

void FieldWidget::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();
    previousMousePosition = mousePosition;
}

QPoint FieldWidget::screenToWorld(QPoint screenCoordinates) const
{
    QPoint worldCoordinates = screenCoordinates;
    worldCoordinates -= cellOffset;
    worldCoordinates.setX(worldCoordinates.x() / cellSize);
    worldCoordinates.setY(worldCoordinates.y() / cellSize);

    return worldCoordinates;
}

void FieldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    if (event->button() == Qt::LeftButton)
    {
        QPoint worldCoordinates = screenToWorld(mousePosition);

        if (worldCoordinates.x() >= 0 &&
                worldCoordinates.y() >= 0 &&
                worldCoordinates.x() < field->getWidth() &&
                worldCoordinates.y() < field->getHeight())
        {
            field->invertCell(worldCoordinates.x(), worldCoordinates.y());
        }
    }

    repaint();
}
