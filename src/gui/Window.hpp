#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

#include "utility.hpp"
#include "Panel.hpp"
#include "MessageHeightException.hpp"
#include "Ships.hpp"
#include "Circle.hpp"
#include "Box.hpp"

class Window
{
private:

	Panel panel;
	std::shared_ptr<arguments> args;
	int collisions = 0;
	const int max_collisions = 2;
	
	void render_frame();
	void play_frames();

public:

	Window(std::shared_ptr<arguments>);
	void activate();

	// Added functions:
	bool detect_shape_avatar_collision();
	void check_for_collisions();
	void setup_ships();
};
