#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#include <libgeodecomp.h>
using namespace LibGeoDecomp;


class CollisionBody;

struct Collision
{
    Collision(CollisionBody &first,
              const CollisionBody &second,
              const FloatCoord<3> &pos1to2,
              const FloatCoord<3> &pos2to1,
              FloatCoord<3> firstCentre,
              FloatCoord<3> secondCentre);
    CollisionBody &first;
    const CollisionBody &second;
    //relative position of collision in fist body's system of reference;
    FloatCoord<3> pos1to2;
    //relative position of collision in second body's system of reference;
    FloatCoord<3> pos2to1;
    FloatCoord<3> firstCentre;
    FloatCoord<3> secondCentre;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
