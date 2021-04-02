#include "Monster.hpp"

Monster::Monster(int health, double strength) :
	health(health),
	strength(strength)
{}

void Monster::damage(int amount)
{ health -= amount; }

int Monster::get_health()
{ return health; }
