#include <header.h>

#ifndef ENEMY_H
#define ENEMY_H

using namespace sf;

class Enemy
{
public:
    RectangleShape en;
    Enemy(float, float, int, int);
    ~Enemy();

    //методы
    void update(float, float, float, int);//вызывается в каждом цикле игры
    void draw(RenderWindow &);//рисует врага на экране
    void die();//убивает врага
    void damage(int);//наносит урон врагу

    //селекторы
    inline float getSpeed()const{return speed;}//скорость движения врага
    inline float getX()const{return x;}//позиция по Х врага
    inline float getY()const{return y;}//позиция по Y врага
    inline bool getLife()const{return life;}//жив ли враг?
    inline bool isOnCenter()const{return onCenter;}//враг в поле игрока?

    //модификаторы
    void setSpeed(const float);//устанвка скорости врага
protected:
    float currentAngle;//угол врага (откуда начал)
    float x;//координата по X
    float y;//координата по Y
    float speed;//скорость врага
    bool life;//жив?
    bool onCenter;//на центре?
    int health;
};


#endif // ENEMY_H
