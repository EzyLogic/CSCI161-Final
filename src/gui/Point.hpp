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

	/// --- Added functions --- ///
	// using ^= because ^ is the exclusive OR, and wanting to exclude the
	// decimal of the double to best evaluate a position in the panel, which
	// uses integers for charting
	const bool operator^= (const Point&);
};
