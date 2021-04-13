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
            std::vector<std::string>{{
				"As a manager, your hunger is insatiable,",
				description,
				info
			}}
		);
	}
	
	return new Dialogue(
		Point(30, 7),
        std::vector<std::string>{{
			"Sorry, you have already eaten your snack.",
			"You will have to let your stomach growl loudly!"
		}}
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
        std::vector<std::string>{{
			"You do not have a snack,",
			"so your manager-sized hunger growls!",
			"---your health only increased by 10 points---"
		}}
	);
}


Dialogue *Manager::attack(Monster &mnstr)
{
	mnstr.damage(5);
	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"You are a manager, and dealt 5 damage to one monster."
		}}
	);
}

Dialogue *Manager::super_power(Monster &mnstr)
{
	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"A manager only dreams of having super powers..."
		}}
	);
}
