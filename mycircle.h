#include <header.h>

#ifndef MYCIRCLE_H
#define MYCIRCLE_H

using namespace sf;

class MyCircle
{
public:
    MyCircle(int, int, int, int, int, int, int, int, int, int, int, int);
    void draw(RenderWindow &);//вывод окружности на экран
private:
    float R;//радиус окружности
    float x;//координата по Х
    float y;//координата по Y
    CircleShape circle;
};

#endif // MYCIRCLE_H
