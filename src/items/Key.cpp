#include "Key.hpp"

Key::Key(Door &door) :
	id(door.id)
{}

void Key::set_id(Door &door)
{ id = door.id; }

void Key::unlock(Door &door)
{
	if (!door.is_open && id == door.id)
		door.is_locked = false;
}

void Key::lock(Door &door)
{
	if (!door.is_open && id == door.id)
		door.is_locked = true;
}
