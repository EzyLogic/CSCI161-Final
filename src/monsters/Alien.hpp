#pragma once

#include <random>
#include <vector>
#include <string>

#include "Monster.hpp"
#include "Player.hpp"
#include "Dialogue.hpp"
#include "Point.hpp"

class Alien : public Monster
{

	int special = rand() % 100;

public:

	Alien(int health, double strength = 30);

	virtual Dialogue *attack(Player&);

};
