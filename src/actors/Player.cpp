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

// Added Functions:
void Player::fill_backpack(Items item) {
    backpack.push_back(item);
}

void Player::set_escaped_collision_true() {
    this->escaped_collision = true;
}

void Player::set_escaped_collision_false() {
    this->escaped_collision = false;
}

void Player::remove_last_item_from_backpack() {
    backpack.pop_back();
}