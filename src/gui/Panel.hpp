#pragma once

#include "Point.hpp"

class Panel {
private:
	static const int WIDTH = 60;
	static const int HEIGHT = 25;
	char pixels[HEIGHT][WIDTH];
	char *output;

	bool check_boundaries(Point&);

public:

	Panel();
	~Panel();
	void fill(char);
	void frame();
	void set(Point, char);
	void draw(Point, Point, char);
	static int get_width()  { return WIDTH; }
	static int get_height() { return HEIGHT; }

};
