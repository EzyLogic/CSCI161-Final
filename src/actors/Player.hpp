#pragma once

#include <string>
#include <vector>

#include "Monster.hpp"
#include "Point.hpp"
#include "Dialogue.hpp"
#include "Snack.hpp"
#include "Items.hpp"

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
	std::string race;

	Point location = Point(0, 0);

	// Added functions:
	std::vector<Items> backpack;
	bool escaped_collision = true;
	
public:

	Player();
	Player(int, double, double, std::string);
	virtual ~Player() {}

	void move(char);
	Point get_location() { return location; }
	void damage(int);
	int get_health() { return health; }
	std::string getRace() { return race; }

	virtual Dialogue *defend() = 0;
	virtual Dialogue *attack(Monster&) = 0;
	virtual Dialogue *eat(Snack&) = 0;
	virtual Dialogue *super_power(Monster&) = 0;

	// Added functions:
	void fill_backpack(Items);
	std::vector<Items> get_backpack() { return backpack; }
	bool get_escaped_collision() { return escaped_collision; }
	void set_escaped_collision_true();
	void set_escaped_collision_false();
	void remove_last_item_from_backpack();
};
