#include "mycircle.h"

using namespace sf;

MyCircle::MyCircle(int r, int OutS, int Cr, int Cg, int Cb, int Cpr, int Px, int Py, int C2r, int C2g, int C2b, int C2pr)
{
    x = Px, y = Py;
    circle.setRadius(r);
    circle.setFillColor(Color(Cr, Cg, Cb, Cpr));
    circle.setPosition(Px, Py);
    circle.setOutlineColor(Color(C2r, C2g, C2b, C2pr));
    circle.setOutlineThickness(OutS);
    circle.setPointCount(200);
}
void MyCircle::draw(RenderWindow &window)
{
    window.draw(circle);
}
