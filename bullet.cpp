#include "bullet.h"

using namespace sf;

Bullet::Bullet(int X, int Y, float Angle)
{
    x = X + 7.5;
    y = Y + 7.5;
    dx = cos(Angle);
    dy = sin(Angle);
    rect.setPosition(x, y);
    rect.setSize(Vector2f(5, 5));
    rect.setFillColor(Color::Red);
    life = true;
}

Bullet::~Bullet()
{
    delete this;
}

void Bullet::update(float time, float baseX, float baseY, int rad)
{
    x += dx*time*0.0001;
    y += dy*time*0.0001;
    if ((x - baseX)*(x - baseX) + (y - baseY)*(y - baseY) >= rad*rad)
        life = false;
    rect.setPosition(x, y);
}

void Bullet::draw(RenderWindow &window)
{
    window.draw(rect);
}

void Bullet::die()
{
    life = false;
}
