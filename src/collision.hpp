#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
#include <libgeodecomp.h>
using namespace LibGeoDecomp;


class CollisionBody;

struct Collision {
  CollisionBody& first;
  CollisionBody& second;
  //relative position of collision;
  FloatCoord<3> pos;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COLLISION_HPP
