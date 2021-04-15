#include "Warrior.hpp"

Warrior::Warrior(std::string race) : Player(120, 15.0, 10.0, race)
{}

void Warrior::set_key(Key &key)
{ this->key = key; }

void Warrior::use_key_unlock(Door &door)
{ key.unlock(door); }

void Warrior::use_key_lock(Door &door)
{ key.lock(door); }


Dialogue *Warrior::defend()
{
	health += 20;
	return new Dialogue(
		Point(30, 7),
		std::vector<std::string>{{
			"You use your holy shield to block an attack,",
			"you suddenly feel better than ever.",
			"---Your health increased by 20 points---"
		}}
	);
}


Dialogue *Warrior::attack(Monster &mnstr)
{
	int amount = rand() % (int)strength;

	mnstr.damage(amount);

	// if you want varialbe numbers to show up in a const char*
	std::string info = "---The monster took " + std::to_string(amount) + " damage---";

	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"You swing your sharpened sword at the monster,",
			"slicing through their armour and skin like butter.",
			info
		}}
	);
}


Dialogue *Warrior::eat(Snack &snack)
{
	return new Dialogue(
		Point(30, 5),
        std::vector<std::string>{{
			"Warrior's don't eat unless the battle has been won."
		}}
	);
}


Dialogue *Warrior::super_power(Monster &mnstr)
{
	int amount = rand() % (int)strength*2 + 20;

    health += amount;
	
	// if you want varialbe numbers to show up in a const char*
	std::string info = 
		"---Your health increased by " +
		std::to_string(amount) +
		" points---";
		
	return new Dialogue(
		Point(30,5),
        std::vector<std::string>{{
			"You get angry and strengthen your resolve.",
			info
		}}
	);
}


