#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "utility.hpp"
#include "Panel.hpp"
#include "MessageWidthException.hpp"

class Window
{
private:

	Panel panel;
	std::shared_ptr<arguments> args;
	
	void render_frame();
	void play_frames();

public:

	Window(std::shared_ptr<arguments>);
	void activate();

};
