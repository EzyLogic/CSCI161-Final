/*
 *Author: Timber Johnson
 *Class: csci 161, assignment 3
 *Instructor: Dr. Russel Campbell
 *Purpose: To show class hierarchy and polymorphism
 *Credit:
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Point.hpp"


class Items {
   private:

      std::string name;
      std::vector<std::string> message;//for menu messages
      Point location;
      char appearance;

   public:

      Items() {}// this was made for clerk's key, so key could be made an Items

      Items(std::string name, Point location, char appearance) :
         name(name),
         location(location),
         appearance(appearance)
      {}

      Items(std::string name, char appearance) :
      name(name),
      appearance(appearance)
      {}

      virtual ~Items() {}

      std::string get_name() { return name; }
      std::vector<std::string> get_message() { return message; }
      Point get_location() { return location; }
      char get_appearance() { return appearance; }

      void set_name(std::string);
      void set_message(std::vector<std::string>);
      void set_location(Point);
      void set_appearance(char);
      void add_to_message(std::string);
};