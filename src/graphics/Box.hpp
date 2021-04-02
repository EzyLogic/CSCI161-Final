#pragma once

#include <cmath>
#include "Shape.hpp"
#include "Panel.hpp"
#include "Point.hpp"

#define PI 3.1415926535

class Box : public Shape
{
private:

    double radius;
    double angle;

public:

    Box(Point centre);
    Box(Point centre, Point delta, double radius, double angle);
    ~Box() {}

    virtual void update();
    virtual void draw();

};
