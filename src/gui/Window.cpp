#include "Window.hpp"

Window::Window(std::shared_ptr<arguments> args) :
	args(args)
{}


// draw into panel here
void Window::render_frame()
{
	panel.fill('`');
	for (Shape *shape : args->shapes)
	{
		shape->set_parent(panel);
		shape->update();
		shape->draw();
	}
	panel.set(args->plyr->get_location(), '@');
}


void Window::activate()
{
	system("clear");
	std::unique_lock<std::mutex> lck(args->mtx);
	lck.unlock();
	while (1)
	{
		if (args->done) break;
		render_frame();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		lck.lock();
		panel.frame();
		printf("Press ESC to exit the game.\n");
		lck.unlock();
		while (args->pause_animation)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	}
}
