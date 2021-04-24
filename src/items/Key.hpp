#pragma once

#include "Door.hpp"
#include "Items.hpp"

class Key : public Items
{

	int id;

public:

	Key() {}
	Key(Door&);

	void set_id(Door&);
	void unlock(Door&);
	void lock(Door&);
};
