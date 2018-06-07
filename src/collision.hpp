#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#include <libgeodecomp.h>
using namespace LibGeoDecomp;


class CollisionBody;

struct Collision
{
    CollisionBody &first;
    const CollisionBody &second;
    //relative position of collision in fist body's system of reference;
    FloatCoord<3> pos1to2;
    //relative position of collision in second body's system of reference;
    FloatCoord<3> pos2to1;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
