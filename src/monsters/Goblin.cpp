#include "Goblin.hpp"

Goblin::Goblin(int health, double strength, std::string name) :
	Monster(health, strength, name)
{}

Dialogue *Goblin::attack(Player &plyr)
{
    int special = rand() % 100;
	if (special > 80)
	{
		plyr.damage(30);
		return new Dialogue(
			Point(30, 18),
			std::vector<std::string>{{
				"The Goblin hits you",
				"with an even bigger rock!",
				"---You take 30 damage---"
			}}
		);
	}

	int amount = rand() % 10 + 2;
	plyr.damage(amount);

	std::string info =
		"---You take " +
		std::to_string(amount) +
		" damage---";

	return new Dialogue(
		Point(30, 18),
		std::vector<std::string>{{
			"The Goblin throws at rock at you!",
			info
		}}
	);
}

