#pragma once

#include <cstdio>
#include <vector>
#include <string>
#include "Panel.hpp"
#include "Point.hpp"

class Player;// not sure why .hpp cannot be included.
    /* Best guess as to why need to forward ddeclare is to do with the virtual
    unctions, and they must be defined by a subclass.
    error was picked up by visual studio. To see: #include "Player.hpp", comment out class Player and hovering over Player part of *player
     */

class Shape
{
protected:

    Panel *parent;
    Point centre;
    char stroke = '*';
    Point delta;

    // Added member:
    Player *player;// for location & compare to HULL to prevent movemement
    bool escaped = false;// copy function from Windows is thing fail
    std::vector<std::string> message;//to give a discription of shape or map
    bool print_message = false;

public:

    Shape(Point centre, Point delta) :
        centre(centre),
        delta(delta)
    {}

    virtual ~Shape() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    // Added functions:
    Point get_centre() { return centre; }
    virtual double get_radius() = 0;
    virtual std::vector<std::string> get_message() = 0;
    bool get_escaped() { return escaped; }
    void set_parent(Panel &parent);
    void set_player(Player *player);
    void set_escaped_true() { this->escaped = true; }
     void set_escaped_false() { this->escaped = false; }
        // set just like parent in Window class
    bool get_print_message() { return print_message; }
    void set_print_message_true();
    void set_print_message_false();
};
