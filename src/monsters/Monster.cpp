#include "Monster.hpp"

Monster::Monster(int health, double strength, std::string name) :
	health(health),
	strength(strength),
	name(name)
{}

void Monster::damage(int amount)
{ health -= amount; }

int Monster::get_health()
{ return health; }
