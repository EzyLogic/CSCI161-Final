#include "Alien.hpp"

Alien::Alien(int health, double strength) :
	Monster(health, strength)
{}

Dialogue *Alien::attack(Player &plyr)
{
	if (special > 80)
	{
		plyr.damage(30);
		return new Dialogue(
			Point(30, 18),
			std::vector<std::string>{{
				"The alien glows and unleases a pulse wave!",
				"---you take 30 damage---"
			}}
		);
	}

	int amount = rand() % 10 + 2;
	plyr.damage(amount);

	std::string info =
		"---you take " +
		std::to_string(amount) +
		" damage---";

	return new Dialogue(
		Point(30, 18),
		std::vector<std::string>{{
			"The alien uses telekenesis and throws debris at you!",
			info
		}}
	);
}

