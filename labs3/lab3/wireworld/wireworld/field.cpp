#include "field.h"


Field::Field()
{
    cells = std::unique_ptr<Cell>(new Cell [height * width]);
    std::fill(cells.get(), cells.get() + height*width, EMPTY);
}

Field::Field(int h, int w)
{
    height = h;
    width = w;
    cells = std::unique_ptr<Cell>(new Cell [height * width]);
    std::fill(cells.get(), cells.get() + height*width, EMPTY);
}


void Field::changeCell(int x, int y)
{
    cells.get()[x*width + y] = (Cell)(((int)(cells.get()[x*width + y]) + 1) % 4);
}

void Field::changeCell(int x, int y, Cell state)
{
    cells.get()[x*width + y] = state;
}

Cell Field::getCell(int x, int y)
{
    return cells.get()[x*width + y];
}

int Field::countHeads(int x, int y)
{
    int result = 0;
    int correct_xmodheight;
    if (0 == x)
    {
      correct_xmodheight = height - 1;
    }
    else
    {
      correct_xmodheight = (x-1)%height;
    }
    if (HEAD == cells.get()[correct_xmodheight*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[correct_xmodheight*width + (y)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[correct_xmodheight*width + (y+1)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[((x)%height)*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[((x)%height)*width + (y+1)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[((x+1)%height)*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[((x+1)%height)*width + (y)%width])
    {
        result++;
    }
    if (HEAD == cells.get()[((x+1)%height)*width + (y+1)%width])
    {
        result++;
    }
    return result;
}
