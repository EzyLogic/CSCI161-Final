#include "Archer.hpp"

Archer::Archer(std::string race) : Player(100, 10.0, 15.0, race)
{}

Dialogue *Archer::eat(Snack &snack)
{
	if (has_snack) {
		health += 40 + snack.health_bonus;

		std::string description = 
			"You eat the " + snack.name + " that you foraged.";

		std::string info = 
			"---Your health increased by " +
			std::to_string(40 + snack.health_bonus) +
			" points---";

		has_snack = false;
		
		return new Dialogue(
			Point(30, 7),
            std::vector<std::string>{{
				description,
				info
			}}
		);
	}
	
	return new Dialogue(
		Point(30, 7),
        std::vector<std::string>{{
			"Good job you wasted your time looking",
			"for food and found none.",
			"Could've killed something instead :/"
		}}
	);
}


Dialogue *Archer::defend()
{
	health += 10;
	return new Dialogue(
		Point(30, 7),
        std::vector<std::string>{{
			"You do some acrobatic stuff",
			"and dodge thousands of arrows.",
			"You think that you're pretty cool",
			"---Your health increased by 10 points---"
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
    int amount = rand() % (int)speed + 100;

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
