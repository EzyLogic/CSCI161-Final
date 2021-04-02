#include "Box.hpp"

Box::Box(Point centre) :
	Shape(
		centre,
		delta
	),
	radius(0),
	angle(0)
{
	stroke = '#';
}

Box::Box(Point centre, Point delta, double radius, double angle) :
	Shape(
		centre,
		delta
	),
	radius(radius),
	angle(angle)
{
	stroke = '#';
}

void Box::update()
{
	centre = Point(centre.x + delta.x, centre.y + delta.y);
	if (centre.x < 0 || parent->get_width() < centre.x) 
		delta = Point(-delta.x, delta.y);
	if (centre.y < 0 || parent->get_height() < centre.y) 
		delta = Point(delta.x, -delta.y);

	angle = (angle + delta.x/10);
	if (angle > 2*PI) angle = 0;
}

void Box::draw()
{
	const int N = 4;
	Point points[4];
	for (int i = 0; i < N; i++)
	{
		points[i].x = radius * cos(2*PI*i/N + angle) + centre.x;
		points[i].y = radius * sin(2*PI*i/N + angle) + centre.y;
	}
	for (int i = 0; i < N-1; i++)
	{
		parent->draw(points[i], points[i+1], stroke);
	}
	parent->draw(points[0], points[N-1], stroke);
}
