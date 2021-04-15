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
	char race;
	if(args->plyr->getRace() == "Human") race = 'h';
	else if(args->plyr->getRace() == "Elf") race = 'e';
    Narrator narrator(race);
    std::vector<std::string> end = { "You've completed all chapters!", "Congrats! Bye!" };
	
	story_action = true; // when false, let user interact with animations instead
	while (!(args->done))
	{
		// allows CPU to rest, and other threads to execute		
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		if (story_action)
		{
            if(narrator.theEnd() == true) {
                prompt_user(end);
                quitGame();
                break;
            }
			// prompt_user will also pause animation to wait for user input
			prompt_user(
				narrator.narrate()
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
			4
		)
	);
	
	// an example of how you could design a function in your game to do things for you
	prompt_user(
		/* deallocated at the end of the Dialogue constructor if no exceptions are thrown! */
		std::vector<std::string>{{
			"Welcome to an Amazing Text Adventure Game!",
			std::string("*** press N to continue ***")
		}}
	);

	prompt = { "Select which race to play as:", "1) Human", "2) Elf" };

    std::string player_description;
    choices = {KEY_1, KEY_2};

    char choice = userInput(prompt, choices);
    std::string race;

	switch(choice)
	{
		case KEY_1:
			race = "Human";
			player_description = std::string(
				"Hello Human!"
			);
			break;
		case KEY_2:
		default:
            race = "Elf";
			player_description = std::string(
				"Greetings Elf!"
			);
			break;
	}

	prompt_user(
		std::vector<std::string>{{
			player_description,
			"",
			press_N
		}}
	);

	prompt = {
        "Select which class to play as:",
        "1) Archer",
        "2) Warrior"
	};
	choice = userInput(prompt, choices);

	lck.lock();
	delete args->plyr;
	args->plyr = nullptr;
	switch(choice)
	{
		case KEY_1:
			args->plyr = new Archer(race);
			player_description = std::string(
				"You chose to be a Archer!"
			);
			break;
		case KEY_2: // if no user input validation, default to Warrior
		default:
			args->plyr = new Warrior(race);
			player_description = std::string(
				"You chose to be a Warrior!"
			);
			break;
	}
	lck.unlock();

	prompt_user(
		std::vector<std::string>{{
			player_description,
			"",
			press_N
		}}
	);
    prompt.clear();
    choices.clear();
}

char Game::userInput(std::vector<std::string> p, std::vector<int> c)
{
    char choice;
    std::vector<std::string> wrong = { "That's not an option", "Please try again" };
    while(1) {
        choice = prompt_user(p);
        for(int i : c) if(choice == i) return choice;

        prompt_user(wrong);
    }
}

void Game::quitGame()
{
    args->done = true;
    delete args->plyr;
}

void Game::random_battle()
{
	std::list<Monster*> monsters;
	if(args->plyr->getRace() == "Human") {
        monsters.push_back(new Goblin( rand() % 20 ));
        monsters.push_back(new Goblin( rand() % 30 ));
	} else if(args->plyr->getRace() == "Elf") {
        monsters.push_back(new Skeleton( rand() % 20 ));
        monsters.push_back(new Skeleton( rand() % 30 ));
	}
    std::string name = monsters.front()->getName();

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
		if(args->plyr->get_health() <= 0) {
		    prompt_user(std::vector<std::string>{{
		        "Oops you're dead!",
		        "Better luck next time.",
		        "Bye!"
		        }}
		    );
            quitGame();
        }
	}

	prompt_user(
        std::vector<std::string>{{
			"You defeated all the " + name + "s!",
			"",
			press_N
		}}
	);

	// continue with next chapter of the story
	story_action = true;
}


void Game::battle_info(std::list<Monster*> &monsters)
{
	std::string num_of_monsters = 
		"There are " + 
		std::to_string(monsters.size()) + " " + monsters.front()->getName() + "(s)";
	std::string mnstr_info1 =
		"The first " + monsters.front()->getName() + " has " +
		std::to_string(monsters.front()->get_health()) +
		" health.";
	std::string mnstr_info2 =
		"The second " + monsters.front()->getName() + " has " +
		std::to_string(monsters.back()->get_health()) +
		" health.";
	std::string plyr_info =
		"Your health is " +
		std::to_string(args->plyr->get_health()) +
		".";

	if (monsters.size() == 2)
	{
		prompt_user(
            std::vector<std::string>{{
				num_of_monsters,
				mnstr_info1,
				mnstr_info2,
				"",
				plyr_info,
				"",
				press_N
			}}
		);
	}
	else
	{
		prompt_user(
            std::vector<std::string>{{
				num_of_monsters,
				mnstr_info1,
				"",
				plyr_info,
				"",
				press_N,
			}}
		);
	}
}


void Game::player_action(std::list<Monster*> &monsters)
{
	prompt = std::vector<std::string>{
        "What do you choose to do:",
        "1) Defend",
        "2) Attack",
        "3) Eat a snack",
        "4) Use your class ability"
	};
	choices = {KEY_1, KEY_2, KEY_3, KEY_4};

	char choice = userInput(prompt, choices);

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
			Snack snack("Mushroom", 10);
			result = args->plyr->eat(snack);
		}
			break;
		case KEY_4:
			result = args->plyr->super_power(*monsters.front());
			break;
	}
	lck.unlock();

	prompt.clear();
    display_result(result); // result memory is moved and deallocated once displayed
}


void Game::monster_action(std::list<Monster*> &monsters)
{
	for (Monster *mnstr : monsters)
	{
		Dialogue *result = mnstr->attack(*args->plyr);
		display_result(result);
	}
}


// Looks unassuming, but allows you to change behaviour of pausing if you want, 
//   separate from default behaviour of prompt_user().
void Game::pause()
{ prompt_user(); }


void Game::display_result(Dialogue *dialogue)
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


char Game::prompt_user(std::vector<std::string> prompt, Point centre)
{
    display_message(
        prompt
    );

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


void Game::display_message(std::vector<std::string> message, Point centre)
{
	try
	{
		args->shapes.push_back(
			new Dialogue(
				centre, /* centre of panel */
				message
			)
		);
	}
	catch (MessageHeightException &e)
	{
		//std::cout << "ERROR: " << e.what() << std::endl;
		// Recovering from error by setting a new message.
		std::vector<std::string> message = e.get_message();
		while ((int)message.size() > Panel::get_height() - 5)
            message.pop_back();

		message.push_back("ERROR: This message is too high.");
		
		args->shapes.push_back(
			new Dialogue(
				centre,
				message
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
