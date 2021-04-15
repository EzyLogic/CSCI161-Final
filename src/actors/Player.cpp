#include "Player.hpp"

Player::Player(int health, double strength, double speed, std::string race) :
    health(health),
    strength(strength),
    speed(speed),
    race(race)
{}

void Player::move(char dir)
{
    switch(dir)
    {
        case UP:
        location = location + Point(0,1);
        break;

        case RIGHT:
        location = location + Point(1, 0);
        break;

        case DOWN:
        location = location + Point(0, -1);
        break;

        case LEFT:
        location = location + Point(-1, 0);
        break;
    }
}


void Player::damage(int amount)
{ health -= amount; }
