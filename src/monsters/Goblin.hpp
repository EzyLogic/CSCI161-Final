#pragma once

#include <random>
#include <vector>
#include <string>

#include "Monster.hpp"
#include "Player.hpp"
#include "Dialogue.hpp"
#include "Point.hpp"

class Goblin : public Monster
{
public:

	Goblin(int health, double strength = 30, std::string name = "Goblin");

	virtual Dialogue *attack(Player&);

};
