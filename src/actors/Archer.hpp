#pragma once

#include <random>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Monster.hpp"
#include "Point.hpp"
#include "Dialogue.hpp"
#include "Snack.hpp"


class Archer : public Player
{
protected:

	bool has_snack = true;

public:

	Archer(std::string);

	virtual Dialogue *defend();
	virtual Dialogue *attack(Monster&);
	virtual Dialogue *eat(Snack&);
	virtual Dialogue *super_power(Monster&);

};
