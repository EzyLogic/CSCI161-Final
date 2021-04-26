/*
 *Author: Timber Johnson
 *Class: csci 161, assignment 3
 *Instructor: Dr. Russel Campbell
 *Purpose: To show class hierarchy and polymorphism
 *Credit: To Russel for some helpfull hints. 
*/
#include "Ships.hpp"
#include "Player.hpp"

Ships::Ships() :
    Shape(centre, delta),
    bomb("bomb", 'B')
{
    key.set_id(door);
    set_print_message_true();
    set_room_locations();
    set_rand_locations();
    set_door_location();
    set_key_location();
    set_bomb_location();
    key.set_appearance('K');
    this->message = std::vector<std::string> {
					"You have been abducted.",
					"Get to the key (K) to unlock",
					"the door (D) to escape.", 
					""
    };    
}

void Ships::update() {
    /* 
     * There was much I wasn't able to finish. Wanted to have a collison 
     * detection funcstion for the HULL of the map using the char HULL for that.
     */
    check_plyr_location_items();
    check_plyr_and_door_when_plyr_at_door();
}

void Ships::draw() {
    draw_perimeter();
    for (Point location : room_locations){
        draw_a_room(location, 3, HULL);
    }
    draw_box(door.get_door_location(), 2.0, 'X');
    parent->set(door.get_door_location(), 'D');
    parent->set(key.get_location(), key.get_appearance());
    parent->set(bomb.get_location(), bomb.get_appearance());    
}

void Ships::draw_box(Point location, double radius, char c) {    
    const int N = 4;
    double angle = PI/4;
    Point points[4];

    for(int i = 0; i < N; i++) {
        points[i].x = radius * cos(2*PI*i/N + angle) + location.x;
        points[i].y = radius * sin(2*PI*i/N + angle) + location.y;
    }
    for (int i = 0; i < N-1; i++)
        parent->draw(points[i], points[i+1], c);
    parent->draw(points[0], points[N-1], c);
}

void Ships::draw_a_room(Point location, double side, char c) {
    Point points[] = {
        Point(location.x + side +3.0, location.y - side),
        Point(location.x + side +3.0, location.y + side),
        Point(location.x - side -3.0, location.y + side),
        Point(location.x - side -3.0, location.y - side)
    };
    
    const int N = sizeof(points)/sizeof(points[0]);
    for (int i = 0; i < N-1; i++)
        parent->draw(points[i], points[i+1], c);
    parent->draw(points[0], points[N-1], c);

    if(location.y > centre.y){
        parent->draw(
            Point(points[0].x -2, points[0].y),
            Point(points[N-1].x +2, points[N-1].y),
            ' '
        );
    } else {
        parent->draw(
            Point(points[1].x -2, points[1].y),
            Point(points[2].x +2, points[2].y),
            ' '
        );
    }
}

void Ships::draw_perimeter() {
    Point points[] = {
        Point(0,0),
        Point((double)parent->get_width()-1, 0),
        Point((double)parent->get_width()-1, (double)Panel::get_height()-1),
        Point(0, (double)parent->get_height()-1)
    };
    parent->draw(points[0], points[1], HULL);
    parent->draw(points[1], points[2], HULL);
    parent->draw(points[2], points[3], HULL);
    parent->draw(points[0], points[3], HULL);
}

void Ships::set_room_locations() {
    this->room_locations = std::vector<Point> {
        Point((double)parent->get_width()*3.0/4.0, (double)parent->get_height()*3/4),
        Point((double)parent->get_width()/4.0, (double)parent->get_height()*3/4),
        Point((double)parent->get_width()/4.0, (double)parent->get_height()/4),
        Point((double)parent->get_width()*3.0/4.0, (double)parent->get_height()/4)
    };
}

void Ships::set_rand_locations() {
    this->rand_locations = std::vector<Point>{
        centre,
        Point(centre.x + parent->get_width()/4, centre.y),
        Point(centre.x - parent->get_width()/4, centre.y),
        Point(centre.x, centre.y + parent->get_height()/4),
        Point(centre.x, centre.y - parent->get_height()/4),
        Point(centre.x + parent->get_width()/4, centre.y + parent->get_height()/4),
        Point(centre.x - parent->get_width()/4, centre.y - parent->get_height()/4)
    };
    for(Point ptr : room_locations) {
        rand_locations.push_back(ptr);
    }
}

void Ships::set_door_location() {
    srand(time(NULL));
    door.set_door_location(
        rand_locations.at( rand() % (int)rand_locations.size() )
    );
    
}

void Ships::set_key_location() {
    srand(time(NULL));
    while(1){
        int location = rand() % (int)rand_locations.size();
        if (rand_locations.at(location).x != door.get_door_location().x
            && rand_locations.at(location).y != door.get_door_location().y)
        {
            if(rand_locations.at(location).x != bomb.get_location().x
            && rand_locations.at(location).y != bomb.get_location().y) {
                key.set_location(rand_locations.at(location));
                break;
            }            
        }
    }
    return;
}

void Ships::set_bomb_location() {
    srand(time(NULL));
    while(1){
        int location = rand() % (int)rand_locations.size();
        if (rand_locations.at(location).x != door.get_door_location().x
            && rand_locations.at(location).y != door.get_door_location().y)
        {
            if(rand_locations.at(location).x != key.get_location().x
            && rand_locations.at(location).y != key.get_location().y) {
                bomb.set_location(rand_locations.at(location));
                break;
            }            
        }
    }
    return;
}

void Ships::check_plyr_location_items() {
    if ((int)player->get_location().x == (int)key.get_location().x
        && (int)player->get_location().y == (int)key.get_location().y) {
        key.set_location(Point ( 0,0 ));
        key.unlock(door);
        door.open();// because there is no get_locked() function to open door.
    }
    // note: ^= does the exact samething as above if. I left that above if
    // statement as is so you can see what is going on. See Point.cpp for more
    if(player->get_location() ^= bomb.get_location()) {
        bomb.set_location(Point ( 0,0 ));
        this->bomb_removed = true;
    }
}

void Ships::check_plyr_and_door_when_plyr_at_door() {
    // Point didn't like && operator, so needed to nest some if's
    if(player->get_location() ^= door.get_door_location()) {
        if(door.get_is_open() == true){
            this->message.clear();
            this->message = std::vector<std::string> {
                "You have unlocked the door."
                "",
                "Press (1) to escape.",
                ""
            };
            if(bomb_removed == true) {
                // I don't know why. Using .pop_back() & .push_back()
                // resulted in segmentation faults
                this->message.clear();
                this->message = std::vector<std::string> {
                    "You have unlocked the door.",
                    "",
                    "Press (1) to escape, or",
                    "press (9) to use the bomb & escape.",
                    ""
                };
            }
        }
        set_escaped_true();
        player->set_escaped_collision_false();        
    }
}

std::vector<std::string> Ships::get_message() {
    return this->message;   }