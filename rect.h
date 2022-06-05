#ifndef RECT_H
#define RECT_H
#include <QPainter>
class QPainter;
class Rect
{
public:
    Rect();
    Rect(int x1, int y1, int x2, int y2, int k);

    int getX1();
    void setX1(int value);

    int getY1();
    void setY1(int value);

    int getX2();
    void setX2(int value);

    int getY2();
    void setY2(int value);

    int getK();
    void setK(int value);

    void draw(QPainter *painter);
    bool contains(int x, int y);


protected:
    int x1, y1, x2, y2, k;
};

#endif // RECT_H
