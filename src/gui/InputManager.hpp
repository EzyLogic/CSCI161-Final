#pragma once

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

#include "utility.hpp"

class InputManager
{

    std::shared_ptr<arguments> args;

    int kbhit(int&, std::mutex&);

public:

    InputManager(std::shared_ptr<arguments>);

    void poll_keypress();

};
