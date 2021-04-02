#pragma once

#include <cstdio>
#include "Panel.hpp"
#include "Point.hpp"

class Shape
{
protected:

    Panel *parent;
    Point centre;
    char stroke = '*';
    Point delta;

public:

    Shape(Point centre, Point delta) :
        centre(centre),
        delta(delta)
    {}

    virtual ~Shape() = 0;

    void set_parent(Panel &parent);
    virtual void update() = 0;
    virtual void draw() = 0;
};
