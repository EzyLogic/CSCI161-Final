#include "Shape.hpp"

Shape::~Shape() {}

void Shape::set_parent(Panel &parent)
{ this->parent = &parent; }
