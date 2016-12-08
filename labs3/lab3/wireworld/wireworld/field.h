#ifndef FIELD_H
#define FIELD_H

typedef enum Cell {
    EMPTY, CONDUCTOR, HEAD, TAIL
} Cell;

class Field
{
public:
    Field();
    ~Field();
    int getHeight() const {
        return height;
    }
    int getWidth() const {
        return width;
    }
    void changeCell(int x, int y);
    void changeCell(int x, int y, Cell state);
    Cell getCell(int x, int y);
    int countHeads(int x, int y);

private:
    static const int DEFAULT_HEIGHT = 20;
    static const int DEFAULT_WIDTH = 20;
    Cell * cells;
    int height;
    int width;
};




#endif // FIELD_H
