//
// Created by evgeny on 5/19/18.
//
#include "collisionBody.hpp"
std::ostream &operator<<(std::ostream &os, const CollisionBody &cb)
{
    os << cb.toPOV();
}