#pragma once

#include <unistd.h>
#include <mutex>
#include <memory>
#include <thread>
#include <chrono>
#include <string>

#include "utility.hpp"
#include "Player.hpp"
#include "Manager.hpp"
#include "Clerk.hpp"
#include "Monster.hpp"
#include "Alien.hpp"
#include "Point.hpp"
#include "Circle.hpp"
#include "Dialogue.hpp"
#include "MessageWidthException.hpp"
#include "Narrator.hpp"

class Game
{
private:

	std::shared_ptr<arguments> args;
	std::unique_lock<std::mutex> lck;
	Narrator narrator;
	bool story_action = false;

	std::string press_N = std::string(">>> press any key to continue <<<");

	// add more keys you might need for your user interaction
	enum keys {
		KEY_ESC = 27,
		// numeric values
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,
		// alphabetic values
		KEY_A = 97,
		KEY_D = 100,
		KEY_S = 115,
		KEY_W = 119
	};

	void get_input();

	void display_message(
		const char**, 
		int,
		// default point is at centre of panel
		Point = Point(Panel::get_width()/2, Panel::get_height()/2)
	);
	
	void remove_message();

public:

	Game(std::shared_ptr<arguments>);

	void loop();

	void setup();

	void random_battle();
	void battle_info(std::list<Monster*>&);
	void player_action(std::list<Monster*>&);
	void monster_action(std::list<Monster*>&);

	// for you to modify, if you need; for example, displaying multiple Dialogue messages
	void pause();
	
	// to display return descriptions of Player and Monster functions, etc.
	void dispaly_result(Dialogue*);
	
	// ask the user to enter a one-keypress choice
	char prompt_user(
		// you can assign default values to parameters, so you do not have to give arguments in a call
		const char** = nullptr,
		int = 1,
		Point = Point(Panel::get_width()/2, 4)
	);

};
