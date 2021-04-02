#include "Dialogue.hpp"

Dialogue::~Dialogue()
{ delete [] message; }


Dialogue::Dialogue(Point centre, const char **lines, int n) :
	Box(centre)
{
	this->n = n;
	message = new std::string[n];
	
	for (int i = 0; i < n; i++)
		message[i] = std::string(lines[i]);
	
	int line_no = 0;
	int w = 4;
	for (int i = 0; i < n; i++)
	{
		if (message[i].length() > (long unsigned int)(w-4)) {
			line_no = i;
			w = message[i].length() + 4;
		}
	}
	
	if (w > Panel::get_width()) 
		throw MessageWidthException(
			"The Dialogue message has line " +
			 std::to_string(line_no) +
			" with " +
			std::to_string(message[line_no].length()) +
			" > " +
			std::to_string(Panel::get_width() - 4) +
			" characters (the width of the panel).",
			message,
			n
		);
	
	//deallocate the strings passed in
	delete [] lines;
}


Dialogue::Dialogue(Dialogue &other) :
	Box(other.centre)
{
	n = other.n;
	message = new std::string[n];
	for (int i = 0; i < n; i++)
		message[i] = std::string(other.message[i]);

}

Dialogue::Dialogue(Dialogue &&other) :
	Box(other.centre)
{
	n = other.n;
	other.n = 0;
	message = other.message;
	other.message = nullptr;
}

void Dialogue::update()
{}

void Dialogue::draw()
{
	int h = n + 4;
	int w = 4;
	for (int i = 0; i < n; i++)
	{
		if (message[i].length() > (long unsigned int)w-4) 
			w = message[i].length() + 4;
	}
	
	Point *points = corner_points(w, h);
	for (int row = points[0].y; row < points[1].y; row++)
		for (int col = points[0].x; col < points[3].x; col++)
			parent->set(Point(col, row), ' ');

	for (int i = 0; i < 3; i++)
	{
		parent->draw(points[i], points[i+1], stroke);;
	}
	parent->draw(points[0], points[3], stroke);

	for (int i = 0; i < n; i++)
	{
		for (size_t j = 0; j < message[i].length(); j++)
		{
			parent->set(
				centre + 
				Point(
					-(int)message[i].length()/2 + (int)j,
					h/2 - 2 - i
				),
				message[i].at(j)
			);
		}
	}

	delete [] points;
}

Point *Dialogue::corner_points(int w, int h)
{	
	int remove = 0;
	if (h%2 == 0) remove = 1; // get rid of extra line for even height
	Point *corners = new Point[4];
	corners[0] = centre + Point(-w/2, remove - h/2);
	corners[1] = centre + Point(-w/2, h/2);
	corners[2] = centre + Point(w/2, h/2);
	corners[3] = centre + Point(w/2, remove - h/2);

	return corners;
}
