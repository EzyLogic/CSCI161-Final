#include "Game.hpp"

Game::Game(std::shared_ptr<arguments> args) :
	args(args)
{
	lck = std::unique_lock<std::mutex>(args->mtx);
	lck.unlock();
}


void Game::loop()
{
	setup();
	
	story_action = true; // when false, let user interact with animations instead
	while (!(args->done))
	{
		// allows CPU to rest, and other threads to execute		
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		if (story_action)
		{
			// prompt_user will also pause animation to wait for user input
			prompt_user(
				narrator.narrate(), //
				narrator.get_no_lines()
			);
			story_action = false;
		}

		// further calls to get_input will only work if you set args->keypress = 0
		// SEE END OF THIS LOOP TO DO SO WITH THREAD LOCKS
		get_input(); // user can press WASD keys to move
		
		if (rand() % 20 == 10)
			random_battle();

		// processing of args->keypress here
		switch(args->keypress) // its mostly fine to read shared thread data without locks
		{
			// player movement
			case KEY_A:
			case KEY_S:
			case KEY_D:
			case KEY_W:
				args->plyr->move(args->keypress);
				break;
			// quit game
			case KEY_ESC:
				args->done = true;
				break;
		}

		// args and its members are shared by all threads
		// YOU MUST LOCK TO ASSIGN NEW VALUES TO SHARED DATA
		lck.lock();
		args->keypress = 0;
		lck.unlock();
	}
}


void Game::setup()
{
	// examples of directly working with classes and objects
	args->shapes.push_back(
		new Circle(
			Point( 10, 3 ),
			3
		)
	);

	args->shapes.push_back(
		new Circle(
			Point( 50, 20 ),
			7
		)
	);
	
	// an example of how you could design a function in your game to do things for you
	prompt_user(
		/* deallocated at the end of the Dialogue constructor if no exceptions are thrown! */
		new const char*[3]{
			"Welcome to an Amazing Text Adventure Game!",
			"*** press N to continue ***",
			"This is an example of a line that is way too long to display and should instead be broken up into multiple lines."
		},
		3
	);

	char choice = prompt_user(
		new const char*[3]{
			"Select which type of person to play as:",
			"1) Manager",
			"2) Clerk"
		},
		3
	);

	std::string player_description;
	lck.lock();
	delete args->plyr;
	args->plyr = nullptr;
	switch(choice)
	{
		case KEY_1:
			args->plyr = new Manager(100, 30.5, 15.0);
			player_description = std::string(
				"You chose to be a manager!"
			);
			break;
		case KEY_2: // if no user input validation, default to clerk
		default:
			args->plyr = new Clerk(120, 20.0, 12.5);
			player_description = std::string(
				"You chose to be a clerk!"
			);
			break;
	}
	lck.unlock();

	prompt_user(
		new const char*[3]{
			player_description.c_str(),
			"",
			press_N.c_str()
		},
		3
	);

}


void Game::random_battle()
{
	std::list<Monster*> monsters;
	monsters.push_back(new Alien( rand() % 20 ));
	monsters.push_back(new Alien( rand() % 30 ));

	while (monsters.size() > 0)
	{
		battle_info(monsters);
		player_action(monsters);
		monster_action(monsters);

		if (monsters.front()->get_health() <= 0) {
			Monster *temp = monsters.front();
			monsters.pop_front();
			delete temp;
		}
	}

	prompt_user(
		new const char*[4]{
			"Congratulations!",
			"You defeated all the monsters!",
			"",
			press_N.c_str()
		},
		4
	);

	// continue with next chapter of the story
	story_action = true;
}


void Game::battle_info(std::list<Monster*> &monsters)
{
	std::string num_of_monsters = 
		"There are " + 
		std::to_string(monsters.size()) +
		" aliens.";
	std::string mnstr_info1 =
		"The first alien has " +
		std::to_string(monsters.front()->get_health()) +
		" health.";
	std::string mnstr_info2 =
		"The second alien has " +
		std::to_string(monsters.back()->get_health()) +
		" health.";
	std::string plyr_info =
		"Your health is " +
		std::to_string(args->plyr->get_health()) +
		".";

	if (monsters.size() == 2)
	{
		prompt_user(
			new const char*[7]{
				num_of_monsters.c_str(),
				mnstr_info1.c_str(),
				mnstr_info2.c_str(),
				"",
				plyr_info.c_str(),
				"",
				press_N.c_str()
			},
			7
		);
	}
	else
	{
		prompt_user(
			new const char*[6]{
				num_of_monsters.c_str(),
				mnstr_info1.c_str(),
				"",
				plyr_info.c_str(),
				"",
				press_N.c_str(),
			},
			6
		);
	}
}


void Game::player_action(std::list<Monster*> &monsters)
{
	char choice = prompt_user(
		new const char*[5]{
			"What do you choose to do:",
			"1) Defend",
			"2) Attack",
			"3) Eat a snack",
			"4) Use your super power!"
		},
		5
	);

	lck.lock();
	Dialogue *result;
	switch(choice)
	{
		case KEY_1:
			result = args->plyr->defend();
			break;
		case KEY_2:
			result = args->plyr->attack(*monsters.front());
			break;
		case KEY_3:
		{// variable in scope of this case only by using braces to make a nested block
			Snack snack("granola bar", 10);
			result = args->plyr->eat(snack);
		}
			break;
		case KEY_4:
			result = args->plyr->super_power(*monsters.front());
			break;
	}
	lck.unlock();
	
	dispaly_result(result); // result memory is moved and deallocated once displayed
}


void Game::monster_action(std::list<Monster*> &monsters)
{
	for (Monster *mnstr : monsters)
	{
		Dialogue *result = mnstr->attack(*args->plyr);
		dispaly_result(result);
	}
}


// Looks unassuming, but allows you to change behaviour of pausing if you want, 
//   separate from default behaviour of prompt_user().
void Game::pause()
{ prompt_user(); }


void Game::dispaly_result(Dialogue *dialogue)
{
	args->shapes.push_back(dialogue);

	std::this_thread::sleep_for(std::chrono::milliseconds(17));
	lck.lock();
	args->pause_animation = true;
	lck.unlock();

	get_input();

	lck.lock();
	args->keypress = 0;
	args->pause_animation = false;
	remove_message();
	lck.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(17));
}


char Game::prompt_user(const char** prompt, int n, Point centre)
{
	// default behaviour
	if (prompt == nullptr)
	{
		display_message(
			new const char*[1]{
				press_N.c_str()
			},
			1,
			Point(Panel::get_width()/2, 4)
		);
	}
	else
	{
		// non-default behaviour where prompt has a list of numbered options for the user to choose among
		display_message(
			prompt,
			n
		);
	}

	lck.lock();
	args->pause_animation = true;
	lck.unlock();

	// Stop user input for half a second to give user a chance to
	//  stop pressing keyboard keys from previous animation interaction gameplay.
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	// The above delay could be removed after implementing user-input validations...
	get_input();

	char user_keypress = args->keypress;

	lck.lock();
	args->keypress = 0;
	args->pause_animation = false;
	remove_message();
	lck.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(17));

	return user_keypress;
}


// --- PRIVATE FUNCTIONS ---

void Game::get_input()
{
	lck.lock();
	args->keypress = 0;
	lck.unlock();
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		if (args->keypress != 0) break;
	}
}


void Game::display_message(const char **message, int n, Point centre)
{
	try
	{
		args->shapes.push_back(
			new Dialogue(
				centre, /* centre of panel */
				message,
				n
			)
		);
	}
	catch (MessageWidthException &e)
	{
		//std::cout << "ERROR: " << e.what() << std::endl;
		// Recovering from error by setting a new message.
		std::string *message = e.get_message();
		int n = e.get_no_lines();
		const char **msg_copy = new const char*[n];
		for (int i = 0; i < n; i++)
			msg_copy[i] = message[i].c_str();
		for (int i = 0; i < n; i++)
		{
			if ((int)message[i].length() > Panel::get_width() - 4)
				msg_copy[i] = "ERROR: This was a line that was too long.";
		}
		
		args->shapes.push_back(
			new Dialogue(
				centre,
				msg_copy,
				n
			)
		);
	}
	// give animation a chance to display new shape at least one frame
	std::this_thread::sleep_for(std::chrono::milliseconds(17));
}


// can really only use this once after each display_message or prompt_user call
void Game::remove_message()
{
	Shape *shape = args->shapes.back();
	args->shapes.pop_back();
	delete shape;
}
