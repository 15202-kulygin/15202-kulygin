#include <QPainter>
#include <QtGui/QMouseEvent>
#include <fstream>
#include "widget.h"
#include "ui_widget.h"

const QColor Widget::GRIDCOLOR = Qt::black;

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(std::unique_ptr<Ui::Widget>(new Ui::Widget))
{
    field = std::unique_ptr<Field>(new Field);
    buffer = std::unique_ptr<Field>(new Field);
    ui.get()->setupUi(this);
}

Widget::~Widget()
{
    //delete field;
    //delete buffer;
    //delete ui;
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
    int FieldWidth = field.get()->getWidth();
    int FieldHeight = field.get()->getHeight();
    for(int i = 0; i <= FieldWidth; i++)
        p.drawLine(i * CELLSIZE, 0, i * CELLSIZE, FieldHeight * CELLSIZE);
    for(int i = 0; i <= FieldHeight; i++)
        p.drawLine(0, i * CELLSIZE, FieldWidth * CELLSIZE, i * CELLSIZE);
}

void Widget::paintField(QPainter &p)
{
    int FieldWidth = field.get()->getWidth();
    int FieldHeight = field.get()->getHeight();
    for(int i = 0; i < FieldHeight; i++)
    {
        for(int j = 0; j < FieldWidth; j++)
        {
            qreal left = (qreal)(CELLSIZE * j);
            qreal top  = (qreal)(CELLSIZE * i);
            QRectF rect(left, top, (qreal)CELLSIZE, (qreal)CELLSIZE);
            QColor CellColor;
            Cell to_get = field.get()->getCell(i, j);
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
   if ((event->y() >= CELLSIZE * field.get()->getHeight()) || (event->x() >= CELLSIZE * field.get()->getWidth()))
       return;
   double cellHeight = event->y() / CELLSIZE;
   double cellWidth = event->x() / CELLSIZE;
   field.get()->changeCell((int)cellHeight, (int)cellWidth);
   buffer.get()->changeCell((int)cellHeight, (int)cellWidth);
   update();
}

void Widget::makeStep()
{
    int fieldHeight = field.get()->getHeight();
    int fieldWidth = field.get()->getWidth();
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            if (EMPTY == buffer.get()->getCell(i, j))
            {
                field.get()->changeCell(i, j, EMPTY);
            }
            else if (HEAD == buffer.get()->getCell(i, j))
            {
                field.get()->changeCell(i, j, TAIL);
            }
            if (TAIL == buffer.get()->getCell(i, j))
            {
                field.get()->changeCell(i, j, CONDUCTOR);
            }
            if (CONDUCTOR == buffer.get()->getCell(i, j))
            {
                if ((2 == buffer.get()->countHeads(i, j)) || (1 == buffer.get()->countHeads(i, j)))
                {
                    field.get()->changeCell(i, j, HEAD);
                }
            }
        }
    }
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            buffer.get()->changeCell(i, j, field.get()->getCell(i, j));
        }
    }
    update();
}

void Widget::clearField()
{
    field = std::unique_ptr<Field>(new Field(field.get()->getHeight(), field.get()->getWidth()));
    buffer = std::unique_ptr<Field>(new Field(field.get()->getHeight(), field.get()->getWidth()));
    update();
}

void Widget::resizeField(int h, int w)
{
    field = std::unique_ptr<Field>(new Field(h, w));
    buffer = std::unique_ptr<Field>(new Field(h, w));
    update();
}

void Widget::saveToFile(std::string text)
{
    std::ofstream file;
    file.open(text);
    int fieldHeight = field.get()->getHeight();
    int fieldWidth = field.get()->getWidth();
    file << "x = " << fieldHeight << ", y = " << fieldWidth << ", rule = WireWorld" << std::endl;
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            Cell to_get = field.get()->getCell(i, j);
            if (EMPTY == to_get)
            {
                file << ".";
            }
            else if (TAIL == to_get)
            {
                file << "T";
            }
            if (CONDUCTOR == to_get)
            {
                file << "C";
            }
            if (HEAD == to_get)
            {
                file << "A";
            }
        }
        file << "$" << std::endl;
    }
    file << "!";
    file.close();
}

void Widget::loadFromFile(std::string text)
{
    std::ifstream file;
    file.open(text);
    if (!file.is_open())
    {
        return;
    }
    char x;
    std::string str;
    int fieldHeight;
    int fieldWidth;
    file >> x >> x >> fieldHeight >> x >> x >> x >> fieldWidth >> x >> str >> str >> str;
    this->resizeField(fieldHeight, fieldWidth);
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            file >> x;
            if ('.' == x)
            {
                field.get()->changeCell(i, j, EMPTY);
            }
            else if ('A' == x)
            {
                field.get()->changeCell(i, j, HEAD);
            }
            else if ('T' == x)
            {
                field.get()->changeCell(i, j, TAIL);
            }
            else if ('C' == x)
            {
                field.get()->changeCell(i, j, CONDUCTOR);
            }
        }
        file >> x;
    }
    file.close();
    update();

}




