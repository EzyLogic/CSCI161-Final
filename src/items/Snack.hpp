#pragma once

#include <string>

// forward declare
class Manager;


class Snack
{

	std::string name;
	int health_bonus;

public:

	Snack(std::string, int);

	friend class Manager;
};
