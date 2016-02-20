#include "enemy.h"

using namespace sf;

Enemy::Enemy(float baseX, float baseY, int windowRadius, int health)
{
    onCenter = false;
    life = true;
    currentAngle = rand() % 360;
    int R = windowRadius;
    x = cos(currentAngle) * R + baseX;
    y = sin(currentAngle) * R + baseY;
    en.setPosition(x, y);
    en.setSize(Vector2f(20, 20));
    en.setFillColor(Color::Green);
    en.setOutlineColor(Color(0, 0, 0, 255));
    en.setOutlineThickness(1);
    speed = 0.000005;
    this->health = health;
}

Enemy::~Enemy()
{
    delete this;
}

void Enemy::update(float baseX, float baseY, float time, int playerRadius)
{
    int R = playerRadius;
    x -= cos(currentAngle) * time * speed * 2;
    y -= sin(currentAngle) * time * speed * 2;
    en.setPosition(x, y);
    if (currentAngle > 360 || currentAngle < -360) currentAngle = 0;
    if ((x - baseX)*(x - baseX) + (y - baseY)*(y - baseY) <= R*R)
        onCenter = true;
    if (this->health <= 0)
        this->die();
    switch(this->health)
    {
    case 1:
        this->en.setFillColor(Color::Green);
        break;
    case 2:
        this->en.setFillColor(Color::Yellow);
        break;
    case 3:
        this->en.setFillColor(Color::Red);
        break;
    case 4:
        this->en.setFillColor(Color::Black);
        break;
    default:
        this->en.setFillColor(Color::Blue);
        break;
    }
}

void Enemy::draw(RenderWindow &window)
{
    window.draw(en);
}

void Enemy::die()
{
    this->health = 0;
    this->life = false;
}

void Enemy::setSpeed(const float sp)
{
    this->speed = sp;
}


void Enemy::damage(int count)
{
    this->health -= count;
}
