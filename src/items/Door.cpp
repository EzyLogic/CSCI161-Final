#include "Door.hpp"

int Door::counter = 0;

Door::Door(bool is_open, bool is_locked) :
	is_open(is_open),
	is_locked(is_locked),
	id(counter++)
{}

void Door::open()
{ is_open = true; }

void Door::close()
{ is_open = false; }

bool Door::get_is_open()
{ return is_open; }
