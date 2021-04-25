/*
 *Author: Timber Johnson
 *Class: csci 161, assignment 3
 *Instructor: Dr. Russel Campbell
 *Purpose: To show class hierarchy and polymorphism
 *Credit:
*/
#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Shape.hpp"
#include "Panel.hpp"
#include "Point.hpp"
#include "Door.hpp"
#include "Key.hpp"
#include "Bomb.hpp"

#define PI 3.1415926535

class Ships : public Shape {
    private:
        Point centre = {
            (parent->get_width())/2.0,
            (parent->get_height())/2.0
        };
        Door door;
        Bomb bomb;
        Key key;
        static const int num_rooms = 4;
        static const char HULL = '=';
        unsigned int items_removed = 0;

        std::vector<Point> room_locations;
        std::vector<Point> rand_locations;

    public:

        //Ship(Point, Point);
        Ships();
        ~Ships() {}

        virtual void update();
        virtual void draw();
        virtual double get_radius() { return 0.0; }
        virtual std::vector<std::string> get_message();
        // getters:
        Point get_centre() { return centre; }

        // setters:
        void set_room_locations();
        void set_rand_locations();
        void set_door_location();
        void set_key_location();
        void set_bomb_location();

        // other functions
        void draw_box(Point, double, char);
        void draw_a_room(Point, double, char);
        void draw_perimeter();
        void check_plyr_location_items();
        void check_plyr_and_door_when_plyr_at_door();
};