#include "Actor.hpp"

Actor::Actor(const float &x, const float &y, const float &rotation)
    : position{x, y}, rotation(rotation) {}

Actor::~Actor() {}