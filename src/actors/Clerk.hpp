#pragma once

#include <random>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Monster.hpp"
#include "Door.hpp"
#include "Key.hpp"
#include "Snack.hpp"
#include "Point.hpp"
#include "Dialogue.hpp"

class Clerk : public Player
{
protected:
	
	Key key;

public:

	Clerk();
	Clerk(int health, double strength, double speed);
	
	void set_key(Key&);
	void use_key_unlock(Door&);
	void use_key_lock(Door&);

	virtual Dialogue *defend();
	virtual Dialogue *attack(Monster&);
	virtual Dialogue *eat(Snack&);
	virtual Dialogue *super_power(Monster&);

};
