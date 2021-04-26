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
		shape->set_player(args->plyr);// added member
		shape->update();
		shape->draw();
	}
	panel.set(args->plyr->get_location(), '@');

	// Added function:
	check_for_collisions();
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


/// --- Added functions: --- ///
bool Window::detect_shape_avatar_collision() {
	Point shapes_location;
	double shapes_radius;
	Point plyr_location = args->plyr->get_location();

	double dx = 0.0;
	double dy = 0.0;
	double distance = 0.0;

	for(Shape *shape : args->shapes) {
		shapes_location = shape->get_centre();
		shapes_radius = shape->get_radius();
		dx = abs(shapes_location.x - plyr_location.x);
		dy = abs(shapes_location.y - plyr_location.y);
		distance = sqrt(dx*dx + dy*dy);
		if(distance <= shapes_radius){
			args->plyr->set_escaped_collision_false();
			return args->plyr->get_escaped_collision();
		}
	}
	args->plyr->set_escaped_collision_true();
	return args->plyr->get_escaped_collision();
}

void Window::check_for_collisions() {
	detect_shape_avatar_collision();
	for(Shape *shape : args->shapes) {
		if (args->plyr->get_escaped_collision() == false
			&& shape->get_escaped() == false
			&& collisions < max_collisions) {
			args->plyr->set_escaped_collision_true();
			collisions++;
			setup_ships();
		}
	}
}

void Window::setup_ships() {
	args->shapes.clear();
	args->shapes.push_back(
		new Ships()
	);
}