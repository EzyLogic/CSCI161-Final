#include <iostream>
#include <iomanip>
#include "Panel.hpp"

Panel::Panel()
{
	output = new char[(WIDTH+1)*HEIGHT+1];
}

Panel::~Panel()
{
	delete [] output;
}

bool Panel::check_boundaries(Point &p)
{
	return 
		0 <= p.x && p.x < WIDTH && 
		0 <= p.y && p.y < HEIGHT;
}

void Panel::fill(char c)
{
	for (int row = 0; row < HEIGHT; row++)
		for (int col = 0; col < WIDTH; col++)
			set(Point(col, row), c);
}

void Panel::frame()
{
	for (int i = HEIGHT-1; i >= 0; i--) {
		for (int j = 0; j < WIDTH; j++)
		output[(HEIGHT-i-1)*(WIDTH+1) + j] = pixels[i][j];
		output[(HEIGHT-i)*(WIDTH+1)-1] = '\n';
	}
	output[HEIGHT*(WIDTH+1)] = 0;
	
	printf("\033[48;2;0;0;0m");
	printf("\033[38;2;255;255;255m");
	// also moves back one frame so that it reduces tear visible in the current frame being printed
	printf("\033[%dA%s\033[%dP", HEIGHT+1, output, 2*HEIGHT+2);
	fflush(stdout);
}

void Panel::set(Point p, char c)
{
	if ( check_boundaries(p) ) 
		pixels[ (int)p.y ][ (int)p.x ] = c;
}

void Panel::draw(Point p, Point q, char c)
{
	// Bresenham's Line Algorithm
	int x1 = p.x;
	int y1 = p.y;
	int x2 = q.x;
	int y2 = q.y;
	short stepx, stepy;

	int dx = x2 - x1;
	int dy = y2 - y1;
	
	if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
	dy <<= 1; // dy is now 2*dy
	dx <<= 1; // dx is now 2*dx
	
	set(Point(x1, y1), c);

	// The algorithm is simplified by ensuring slope m is always -1 < m < 1.
	if (dx > dy) {
		int error = dy - (dx >> 1);
		while (x1 != x2) {
			x1 += stepx;
			error += dy;
			if (error >= 0) {
				y1 += stepy;
				error -= dx;
			}
			set(Point(x1, y1), c);
		}
	} else { // but this means we may have to swap roles of dy and dx
		int error = dx - (dy >> 1);
		while (y1 != y2) {
			y1 += stepy;
			error += dx;
			if (error >= 0) {
				x1 += stepx;
				error -= dy;
			}
			set(Point(x1, y1), c);
		}
	}
}
