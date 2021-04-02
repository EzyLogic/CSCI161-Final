#pragma once

#include "Door.hpp"

class Key
{

	int id;

public:

	Key() {}
	Key(Door&);

	void set_id(Door&);
	void unlock(Door&);
	void lock(Door&);
};
