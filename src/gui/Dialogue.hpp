#pragma once

#include <iostream>
#include <string>
#include "Point.hpp"
#include "Box.hpp"
#include "MessageWidthException.hpp"

class Dialogue : public Box
{

	int n;
	std::string *message;

	Point* corner_points(int, int);

public:

	Dialogue(Point, const char**, int);
	Dialogue(Dialogue&);
	Dialogue(Dialogue&&);
	~Dialogue();

	virtual void update();
	virtual void draw();
};
