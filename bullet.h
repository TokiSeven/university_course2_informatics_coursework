#include <header.h>

#ifndef BULLET_H
#define BULLET_H

using namespace sf;

class Bullet
{
public:
    Bullet(int, int, float);
    ~Bullet();

    //методы
    void update(float, float, float, int);//вызывается в каждом цикле игры
    void draw(RenderWindow &);//рисует пулю в окне
    void die();//уничтожает пулю

    //селекторы
    inline float getX()const{return rect.getPosition().x;}//позиция пули по Х
    inline float getY()const{return rect.getPosition().y;}//позиция пули по Y
    inline float getW()const{return rect.getSize().x;}//ширина пули
    inline float getH()const{return rect.getSize().y;}//высота пули
    inline bool getLife()const{return life;}//существует ли пуля
private:
    float x;//координата пули по X
    float y;//координата пули по Y
    float dx;//скорость пули по X
    float dy;//скорость пули по Y
    bool life;//жива ли пуля (попала в кого, вышла за пределы карты или летит)
    RectangleShape rect;
};

#endif // BULLET_H
