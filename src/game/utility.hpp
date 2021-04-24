#pragma once

#include <mutex>
#include <list>
#include <vector>
#include <iostream>
#include "Player.hpp"
#include "Warrior.hpp"
#include "Shape.hpp"

struct arguments
{
	// a mutex helps coordinate locking of threads so 
	//   they can share data one at a time without conflicts
	std::mutex mtx;
	// to signal to all threads to stop looping
	bool done = false;
	bool pause_animation = false;

	// game data
	Player *plyr = new Warrior("Human"); // before the user chooses a type of Player

	/// --- change shapes to vector from list --- ///
	std::vector<Shape*> shapes;
	char keypress;

	arguments() {}

	~arguments()
	{
		for (Shape *shape : shapes)
			delete shape;
	}
};
