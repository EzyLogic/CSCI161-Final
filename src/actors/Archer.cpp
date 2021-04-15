#include "Archer.hpp"

Archer::Archer(std::string race) : Player(100, 10.0, 15.0, race)
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
		Point(30, 5),
        std::vector<std::string>{{
			"Sorry, you have already eaten your snack."
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
    int amount = rand() % (int)strength;

    mnstr.damage(amount);

    // if you want varialbe numbers to show up in a const char*
    std::string info = "---The monster took " + std::to_string(amount) + " damage---";

    return new Dialogue(
        Point(30, 5),
        std::vector<std::string>{{
        "You draw your bow and fire an arrow,",
        "the arrow flies through the air and hits the monster.",
        info
		}}
	);
}

Dialogue *Archer::super_power(Monster &mnstr)
{
    int amount = rand() % (int)speed + 10;

    mnstr.damage(amount);

    std::string info = "---The monster took " + std::to_string(amount) + " damage---";

	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"You give a command to your pet to attack the monster,",
            "your pet bites the monster so you give them a treat.",
            info
		}}
	);
}
