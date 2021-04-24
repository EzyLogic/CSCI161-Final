/*
 *Author: Timber Johnson
 *Class: csci 161, assignment 3
 *Instructor: Dr. Russel Campbell
 *Purpose: To show class hierarchy and polymorphism
 *Credit:
*/
#include "Items.hpp"

void Items::set_name(std::string name) {
   this->name = name;
}
   
void Items::set_message(std::vector<std::string> message) {
   this->message = message;
}

void Items::set_location(Point location) {
   this->location = location;
}

void Items::set_appearance(char appearance) {
   this->appearance = appearance;
}

void Items::add_to_message(std::string message) {
   this->message.push_back(message);
}