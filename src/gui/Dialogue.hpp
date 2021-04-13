#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Point.hpp"
#include "Box.hpp"
#include "MessageHeightException.hpp"

class Dialogue : public Box
{

	std::vector<std::string> message;

	Point* corner_points(int, int);

public:

	Dialogue(Point, std::vector<std::string>);
	Dialogue(Dialogue&);
	Dialogue(Dialogue&&);
	~Dialogue();

	virtual void update();
	virtual void draw();
};
