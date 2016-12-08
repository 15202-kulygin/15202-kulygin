#include "field.h"

Field::Field()
{
    height = DEFAULT_HEIGHT;
    width = DEFAULT_WIDTH;
    cells = new Cell [height * width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            cells[i*width + j] = EMPTY;
        }
    }
}

Field::~Field()
{
    delete [] cells;
    height = 0;
    width = 0;
}

void Field::changeCell(int x, int y)
{
    cells[x*width + y] = (Cell)(((int)(cells[x*width + y]) + 1) % 4);
}

void Field::changeCell(int x, int y, Cell state)
{
    cells[x*width + y] = state;
}

Cell Field::getCell(int x, int y)
{
    return cells[x*width + y];
}

int Field::countHeads(int x, int y)
{
    int result = 0;
    if (HEAD == cells[((x-1)%height)*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells[((x-1)%height)*width + (y)%width])
    {
        result++;
    }
    if (HEAD == cells[((x-1)%height)*width + (y+1)%width])
    {
        result++;
    }
    if (HEAD == cells[((x)%height)*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells[((x)%height)*width + (y+1)%width])
    {
        result++;
    }
    if (HEAD == cells[((x+1)%height)*width + (y-1)%width])
    {
        result++;
    }
    if (HEAD == cells[((x+1)%height)*width + (y)%width])
    {
        result++;
    }
    if (HEAD == cells[((x+1)%height)*width + (y+1)%width])
    {
        result++;
    }
    return result;
}
