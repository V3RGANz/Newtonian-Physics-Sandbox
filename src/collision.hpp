#ifndef COLLISION_HEADER
#define COLLISION_HEADER
#include "collisionBody.hpp"
using namespace LibGeoDecomp;

template<class Shape>
struct Collision {
  CollisionBody<Shape>& other;
  //relative position of collision;
  FloatCoord<3> pos;
};

#endif // !COLLISION_HEADER
