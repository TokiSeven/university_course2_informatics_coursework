#include "mainclass.h"

using namespace sf;

mainClass::mainClass()
{
    winW = 700;
    winH = 700;
    winR = 300;
    playerR = winR / 3;
    speed = 0.000005;
    Volume = 60;
    Win = 0;
    kEnemys = 5;
    kSpeedEn = 2;
}

void mainClass::setCountEnemy(const int x)
{
    kEnemys = x;
}
void mainClass::setWinner(const int x)
{
    Win = x;
}
void mainClass::setMouseX(const int x)
{
    mX = x;
}
void mainClass::setMouseY(const int x)
{
    mY = x;
}
void mainClass::setCountSpeedEnemy(const int x)
{
    kSpeedEn = x;
}
