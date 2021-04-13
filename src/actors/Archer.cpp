#include "Archer.hpp"

Archer::Archer() : Player(100, 30.5, 15.0)
{}

Dialogue *Archer::eat(Snack &snack)
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
				"As a Archer, your hunger is insatiable,",
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


Dialogue *Archer::defend()
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
			"so your Archer-sized hunger growls!",
			"---your health only increased by 10 points---"
		}}
	);
}


Dialogue *Archer::attack(Monster &mnstr)
{
	mnstr.damage(5);
	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"You are a Archer, and dealt 5 damage to one monster."
		}}
	);
}

Dialogue *Archer::super_power(Monster &mnstr)
{
	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"A Archer only dreams of having super powers..."
		}}
	);
}
