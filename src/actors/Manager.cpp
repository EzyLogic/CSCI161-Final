#include "Manager.hpp"

Manager::Manager(int health, double strength, double speed) :
	Player(health, strength, speed)
{}

Dialogue *Manager::eat(Snack &snack)
{
	if (has_snack) {
		health += 40 + snack.health_bonus;

		std::string description = 
			"so you scarf down that " +
			snack.name +
			"!";

		std::string info = 
			"---your health increased by " +
			std::to_string(40 + snack.health_bonus) +
			" points---";

		has_snack = false;
		
		return new Dialogue(
			Point(30, 7),
			new const char*[3]{
				"As a manager, your hunger is insatiable,",
				description.c_str(),
				info.c_str()
			},
			3
		);
	}
	
	return new Dialogue(
		Point(30, 7),
		new const char*[2]{
			"Sorry, you have already eaten your snack.",
			"You will have to let your stomach growl loudly!"
		},
		2
	);
}


Dialogue *Manager::defend()
{
	if (has_snack)
	{
		Snack snack("granola bar", 10);
		return eat(snack);
	}
	
	health += 10;
	return new Dialogue(
		Point(30, 7),
		new const char*[3]{
			"You do not have a snack,",
			"so your manager-sized hunger growls!",
			"---your health only increased by 10 points---"
		},
		3
	);
}


Dialogue *Manager::attack(Monster &mnstr)
{
	mnstr.damage(5);
	return new Dialogue(
		Point(30, 5),
		new const char*[1]{
			"You are a manager, and dealt 5 damage to one monster."
		},
		1
	);
}

Dialogue *Manager::super_power(Monster &mnstr)
{
	return new Dialogue(
		Point(30, 5),
		new const char*[1]{
			"A manager only dreams of having super powers..."
		},
		1
	);
}
