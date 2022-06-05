#include "rect.h"
#include <QPainter>
#include <QList>
class QPainter;

Rect::Rect()
    :Rect(0,0,0,0,0){}
Rect::Rect(int x1, int y1, int x2, int y2, int k)
    :x1(x1), y1(y1), x2(x2), y2(y2), k(k)
{
//    this->x1 = x1;
//    this->y1 = y1;
//    this->x2 = x2;
//    this->y2 = y2;
//    this->k = k;
}
int Rect::getX1()
{
    return x1;
}

void Rect::setX1(int value)
{
    x1 = value;
}

int Rect::getY1()
{
    return y1;
}

void Rect::setY1(int value)
{
    y1 = value;
}

int Rect::getX2()
{
    return x2;
}

void Rect::setX2(int value)
{
    x2 = value;
}

int Rect::getY2()
{
    return y2;
}

void Rect::setY2(int value)
{
    y2 = value;
}

int Rect::getK()
{
    return k;
}

void Rect::setK(int value)
{
    k = value;
}

void Rect::draw(QPainter *painter)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::NoBrush);
    if (this->k==6 || this->k > 6)
        painter->setBrush(Qt::black);
    else if (this->k == 6)
        painter->setBrush(Qt::blue);
    else if (this->k == 4)
        painter->setBrush(Qt::green);
    else if (this->k == 3)
        painter->setBrush(Qt::yellow);
    else if (this->k == 2)
        painter->setBrush(Qt::red);
    else if (this->k == 1 || this->k == 0)
        painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawRect(this->x1, this->y1, this->x2 - this->x1, this->y2 - this->y1);
}

bool Rect::contains(int x, int y)
{
    return((x > this->x1) && (y > this->y1) && (x < this->x2) && (y < this->y2));
}
