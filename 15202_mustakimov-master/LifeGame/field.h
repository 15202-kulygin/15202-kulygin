#ifndef FIELD_H
#define FIELD_H


class Field
{
public:
    Field(int width = 15, int height = 15);

    bool getCell(int x, int y) const;
    void setCell(int x, int y, bool value);
    void invertCell(int x, int y);

    void clearField();
    void randomizeField();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void step(int count);

private:
    int width;
    int height;

    int getNeighboursCount(int x, int y) const;
    void stepOnce();

    bool * cells;
};

#endif // FIELD_H
