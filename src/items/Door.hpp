#pragma once

#include "Point.hpp"

class Key;

class Door
{
    static int counter;

    bool is_open = false;
    bool is_locked = true;
    int id;

    // Added member:
    Point door_location;

public:

    Door() {}
    Door(bool, bool = false);

    void open();
    void close();
    bool get_is_open();

    friend class Key;

    // Added functions:
    Point get_door_location() { return door_location; }
    void set_door_location(Point);
};
