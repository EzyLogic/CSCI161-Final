#include "main.hpp"

int main()
{
	struct termios oldt, newt;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ECHO);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

	std::shared_ptr<arguments> args = std::make_shared<arguments>();

	std::thread user_interaction(play, args);
	std::thread input(keyboard_events, args);
	std::thread gui(animate, args);

	gui.join();
	input.join();
	user_interaction.join();
	//std::cout << "Finished executing threads." << std::endl;
	
	oldt.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	system("clear");

	return EXIT_SUCCESS;
}


void keyboard_events(std::shared_ptr<arguments> args)
{
	InputManager in(args);
	in.poll_keypress();
}


void play(std::shared_ptr<arguments> args)
{
	Game game(args);
	game.loop();
	//std::cout << "Finished Game thread." << std::endl;
}


void animate(std::shared_ptr<arguments> args)
{
	Window window(args);
	window.activate();
	//std::cout << "Finished Animate thread." << std::endl;
}
