#pragma once

#include "Shape.hpp"
#include "Panel.hpp"
#include "Point.hpp"

class Circle : public Shape
{
private:

    double radius;

    void draw_symmetry(int x, int y);

public:

    Circle(Point centre, double radius);
    ~Circle() {}

    virtual void update();
    virtual void draw();

};
