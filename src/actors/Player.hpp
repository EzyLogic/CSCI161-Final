#pragma once

#include <string>

#include "Monster.hpp"
#include "Point.hpp"
#include "Dialogue.hpp"
#include "Snack.hpp"

class Player
{
protected:

	enum direction { 
		UP = 119, 
		RIGHT = 100, 
		DOWN = 115, 
		LEFT = 97 
	};

	int health;
	double strength;
	double speed;

	Point location = Point(0, 0);
	
public:

	Player();
	Player(int, double, double);
	virtual ~Player() {}

	void move(char);
	Point get_location() { return location; }
	void damage(int);
	int get_health() { return health; }

	virtual Dialogue *defend() = 0;
	virtual Dialogue *attack(Monster&) = 0;
	virtual Dialogue *eat(Snack&) = 0;
	virtual Dialogue *super_power(Monster&) = 0;

};
