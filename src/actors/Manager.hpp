#pragma once

#include <string>
#include <vector>
#include "Player.hpp"
#include "Monster.hpp"
#include "Point.hpp"
#include "Dialogue.hpp"
#include "Snack.hpp"


class Manager : public Player
{
protected:

	bool has_snack = true;

public:

	Manager() {}
	Manager(int health, double strength, double speed);

	virtual Dialogue *defend();
	virtual Dialogue *attack(Monster&);
	virtual Dialogue *eat(Snack&);
	virtual Dialogue *super_power(Monster&);

};
