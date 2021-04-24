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


    // Added functions:
    virtual double get_radius() { return radius; }
    virtual std::vector<std::string> get_message() { return message; }
};
