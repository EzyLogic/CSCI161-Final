#include "Dialogue.hpp"

Dialogue::~Dialogue()
{}


Dialogue::Dialogue(Point centre, std::vector<std::string> lines) :
	Box(centre)
{
	message.swap(lines);

	if ((int)message.size() > Panel::get_height() - 4)
	    throw MessageHeightException(
	            "The Dialogue message has " +
	            std::to_string(message.size()) +
                " number of lines " +
                " > " +
                std::to_string(Panel::get_height() - 4) +
                " lines (the height of the panel).",
                message
        );
}


Dialogue::Dialogue(Dialogue &other) :
	Box(other.centre)
{
    message = std::vector<std::string>(other.message);
}

Dialogue::Dialogue(Dialogue &&other) :
	Box(other.centre)
{
	message = std::move(other.message);
}

void Dialogue::update()
{}

void Dialogue::draw()
{
    int n = message.size();
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
		parent->draw(points[i], points[i+1], stroke);
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
