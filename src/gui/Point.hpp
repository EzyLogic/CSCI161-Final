#pragma once

class Point
{
public:
	double x = 0;
	double y = 0;

	Point() {}
	Point(double x, double y) : x(x), y(y) {}

    const Point operator= (const Point&);
	const Point operator+ (const Point&);
};
