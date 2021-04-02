#include "Circle.hpp"

Circle::Circle(Point centre, double radius) :
    Shape(
        centre,
        Point(0.25, 0.25) /* delta */
    ),
    radius(radius)
{}

void Circle::update()
{
    centre = Point(centre.x + delta.x, centre.y + delta.y);
    if (centre.x < 0 || parent->get_width() < centre.x) 
        delta = Point(-delta.x, delta.y);
    if (centre.y < 0 || parent->get_height() < centre.y) 
        delta = Point(delta.x, -delta.y);
}

void Circle::draw() {
    // Bresenham's Circle algorithm
    int x = 0;
    int y = radius;
    int d = 3 - 2*radius;
    draw_symmetry(x, y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4*(x - y) + 10;
        } else {
            d = d + 4*x + 6;
        }
        draw_symmetry(x, y);
    }
}
	
void Circle::draw_symmetry(int x, int y) {
    // the eight symmetric points on this circle of the point (x, y)
    parent->set(Point{centre.x + x, centre.y + y}, stroke);
    parent->set(Point{centre.x - x, centre.y + y}, stroke);
    parent->set(Point{centre.x + x, centre.y - y}, stroke);
    parent->set(Point{centre.x - x, centre.y - y}, stroke);
    parent->set(Point{centre.x + y, centre.y + x}, stroke);
    parent->set(Point{centre.x - y, centre.y + x}, stroke);
    parent->set(Point{centre.x + y, centre.y - x}, stroke);
    parent->set(Point{centre.x - y, centre.y - x}, stroke);
}