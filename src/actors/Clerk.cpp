#include "Clerk.hpp"

Clerk::Clerk(int health, double strength, double speed) :
	Player(health, strength, speed)
{}

void Clerk::set_key(Key &key)
{ this->key = key; }

void Clerk::use_key_unlock(Door &door)
{ key.unlock(door); }

void Clerk::use_key_lock(Door &door)
{ key.lock(door); }


Dialogue *Clerk::defend()
{
	health += 20;
	return new Dialogue(
		Point(30, 7),
		std::vector<std::string>{{
			"You did what diligent employees do best,",
			"and took a break to rest!",
			"---your health increased by 20 points---"
		}}
	);
}


Dialogue *Clerk::attack(Monster &mnstr)
{
	int amount = rand() % (int)strength + 10;

	mnstr.damage(amount);

    const char *result[3]{
		"The alien bleeds a prick of green blood.",
		"The alien screams in shock.",
		"This alien does not seem to be bothered."
	};

	// if you want varialbe numbers to show up in a const char*
	std::string info = 
		"---the alien was dealt " +
		std::to_string(amount) +
		" damage---";

	return new Dialogue(
		Point(30, 7),
        std::vector<std::string>{{
			"Using your trusty nametag pin, you stab the alien!,",
			result[rand() % 3],
			info
		}}
	);
}


Dialogue *Clerk::eat(Snack &snack)
{
	return new Dialogue(
		Point(30, 6),
        std::vector<std::string>{{
			"Sorry, the clerk does not like to snack."
		}}
	);
}


Dialogue *Clerk::super_power(Monster &mnstr)
{
	int amount = rand() % (int)strength*2 + (int)speed;

	mnstr.damage(amount);

	std::string result[2]{
		"Half of the alien is crusted with black scortches.",
		"Screaming in horror, the alien falls to their knees."
	};
	
	// if you want varialbe numbers to show up in a const char*
	std::string info = 
		"---the alien was dealt " +
		std::to_string(amount) +
		" damage---";
		
	return new Dialogue(
		Point(30,9),
        std::vector<std::string>{{
			"You raise your hands...,",
			"They begin to glow with fire...",
			"You blast a fireball from your hands at the alien!",
			result[rand() % 2],
			info
		}}
	);
}


