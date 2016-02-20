#include <header.h>

#ifndef MAINCLASS_H
#define MAINCLASS_H

using namespace sf;

class mainClass
{
public:
    mainClass();

    //селекторы
    inline int getWindowWidth()const{return winW;}//вернет ширину окна
    inline int getWindowHeight()const{return winH;}//вернет высоту окна
    inline int getWindowRadius()const{return winR;}//вернет радиус внешней окружности
    inline int getPlayerRadius()const{return playerR;}//вернет радиус окружности игрока
    inline float getSpeed()const{return speed;}//вернет скорость игры
    inline float getVolume()const{return Volume;}//вернет громкость звуковых эффектов
    inline int getMouseX()const{return mX;}//вернет позицию мыши по Х
    inline int getMouseY()const{return mY;}//вернет позицию мыши по Y
    inline int getWinner()const{return Win;}//вернет константу для победы (победил/проиграл/пауза)
    inline int getCountEnemy()const{return kEnemys;}//количество врагов максимальное на данном этапе игры
    inline int getCountSpeedEnemy()const{return kSpeedEn;}//скорость врагов

    //модификаторы
    void setCountEnemy(const int);//установка количества врагов
    void setWinner(const int);//установка победы/поражения/паузы
    void setMouseX(const int);//установка позиции мыши по Х
    void setMouseY(const int);//установка позиции мыши по Y
    void setCountSpeedEnemy(const int);//установка скорость врагам
private:
    int winW;//размер окна - ширина
    int winH;//размер окна - высота
    int winR;//размер главного круга (радиус)
    int playerR;//размер области игрока (радиус)
    float speed;//константа для скорости (НЕ МЕНЯТЬ!!!)
    float Volume;//громкость музыки (всех звуков)
    int mX;//позиция мыши по ОХ
    int mY;//позиция мыши по ОY
    int Win;//константа для победы
    int kEnemys;//кол-во врагов в начале
    int kSpeedEn;//коэффициент ускорения врагов
};

#endif // MAINCLASS_H
