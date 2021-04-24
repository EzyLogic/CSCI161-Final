#include "Shape.hpp"

Shape::~Shape() {}

void Shape::set_parent(Panel &parent)
{ this->parent = &parent; }


// Added functions:
void Shape::set_parent(Panel &parent) {
   this->parent = &parent; }
// not a fan of this, but best I could do with time had
void Shape::set_player(Player *player) {
   this->player = player;
}

// Added functions:
void Shape::set_print_message_true() {
    this->print_message = true;
}

void Shape::set_print_message_false() {
    this->print_message = false;
}