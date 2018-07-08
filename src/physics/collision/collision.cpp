#include "collision.hpp"
Collision::Collision(CollisionBody &first,
                     const CollisionBody &second,
                     const FloatCoord<3> &pos1to2,
                     const FloatCoord<3> &pos2to1)
    : first(first), second(second), pos1to2(pos1to2), pos2to1(pos2to1)
{}
