#include "Skeleton.hpp"

Skeleton::Skeleton(int health, double strength, std::string name) :
    Monster(health, strength, name)
{}

Dialogue *Skeleton::attack(Player &plyr)
{
    int special = rand() % 100;
	if (special > 80)
	{
		plyr.damage(25);
		return new Dialogue(
			Point(30, 18),
			std::vector<std::string>{{
				"The skeleton rips off a rib and",
				"stabs you with it. Ouch!",
				"---You take 25 damage---"
			}}
		);
	}

	int amount = rand() % 10;
	plyr.damage(amount);

	std::string info =
		"---You take " +
		std::to_string(amount) +
		" damage---";

	return new Dialogue(
		Point(30, 18),
		std::vector<std::string>{{
			"The skeleton shoots an arrow at you.",
			info
		}}
	);
}
