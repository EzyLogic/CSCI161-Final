#pragma once

#include <string>

// forward declare
class Archer;


class Snack
{

	std::string name;
	int health_bonus;

public:

	Snack(std::string, int);

	friend class Archer;
};
