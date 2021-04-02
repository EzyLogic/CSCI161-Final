#include "Point.hpp"

const Point Point::operator= (const Point &other)
{
	x = other.x;
	y = other.y;
	return *this;
}

const Point Point::operator+ (const Point &other)
{
	Point temp;
	temp.x += x + other.x;
	temp.y += y + other.y;
	return temp;
}
