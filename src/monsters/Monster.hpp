#pragma once

#include <string>
#include "Dialogue.hpp"

// circular dependency, so forward declare one of the declarations
class Player;


class Monster
{
protected:

	int health;
	double strength;
	std::string name;

public:

	Monster() {}
	Monster(int, double, std::string);

	virtual ~Monster() {}

	void damage(int);
	int get_health();
	std::string getName() { return name; }

	virtual Dialogue *attack(Player &) = 0;

};
