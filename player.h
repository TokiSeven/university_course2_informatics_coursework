#include <header.h>

#ifndef PLAYER_H
#define PLAYER_H

using namespace sf;

class Player
{
public:
    Player(float, float, int);

    //методы
    void update(float, float);//производимые действия игрока
    void show(RenderWindow &);//вывод игрока на экран

    //селекторы
    inline float getAngle()const{return currentAngle;}//угол поворота игрока
    inline float getX()const{return x;}//позиция игрока по X
    inline float getY()const{return y;}//позиция игрок по Y

    //модификаторы
    void setX(const float);//установка позиции игрока по X
    void setY(const float);//установка позиции игрока по Y
    void setAngle(const float);//установка угла поворота игрока
private:
    float currentAngle;//текущий угол игрока (его поворот)
    float x;//координата по Х
    float y;//координата по Y
    float R;//радиус игрока
    CircleShape p;
};

#endif // PLAYER_H
