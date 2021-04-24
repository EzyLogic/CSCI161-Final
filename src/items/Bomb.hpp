/*
 *Author: Timber Johnson
 *Partner: Brenden Gray
 *Class: csci 161, assignment 3
 *Instructor: Dr. Russel Campbell
 *Purpose: To show class hierarchy and polymorphism
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Items.hpp"
#include "Point.hpp"

class Bomb : public Items {
   private:

   public:
      Bomb() {}

      Bomb(std::string, char);
};