#include "collisionBody.hpp"
std::ostream &operator<<(std::ostream &os, const CollisionBody &cb)
{
    os << cb.toPOV();
}