#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <algorithm>
#include <cstring>

#include "utility.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "MessageHeightException.hpp"

// thread function prototypes
void play(std::shared_ptr<arguments>);
void keyboard_events(std::shared_ptr<arguments>);
void animate(std::shared_ptr<arguments>);
