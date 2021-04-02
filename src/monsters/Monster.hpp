#pragma once

#include "Dialogue.hpp"

// circular dependency, so forward declare one of the declarations
class Player;


class Monster
{
protected:

	int health;
	double strength;

public:

	Monster() {}
	Monster(int, double);

	virtual ~Monster() {}

	void damage(int);
	int get_health();

	virtual Dialogue *attack(Player &) = 0;

};
