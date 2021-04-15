#pragma once

#include <random>
#include <vector>
#include <string>

#include "Monster.hpp"
#include "Player.hpp"
#include "Dialogue.hpp"
#include "Point.hpp"

class Skeleton : public Monster
{

public:

    Skeleton(int health, double strength = 20, std::string name = "Skeleton");

    virtual Dialogue *attack(Player&);
};