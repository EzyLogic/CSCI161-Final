#include "InputManager.hpp"


InputManager::InputManager(std::shared_ptr<arguments> args) :
    args(args)
{}

void InputManager::poll_keypress()
{
	int key_hit = 0;
    std::unique_lock<std::mutex> lck(args->mtx);
    lck.unlock();
	while (1) 
	{
		key_hit = 0;
		while (!kbhit(key_hit, args->mtx) && !args->done) {
			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		lck.lock();
		args->keypress = key_hit;
		
        if (args->done) break;
		lck.unlock();
	}
	lck.unlock(); // after a break---otherwise, other threads may be left waiting
}

// You are NOT expected to understand this function!
// https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
// user: itsme86, date: 03-17-2005
int InputManager::kbhit(int &k, std::mutex &mtx)
{
    std::unique_lock<std::mutex> lck(mtx);
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	oldt.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		k = ch;
		lck.unlock();
		return 1;
	}
	lck.unlock();
	return 0;
}
