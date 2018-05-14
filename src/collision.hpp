#ifndef COLLISION_HEADER
#define COLLISION_HEADER
#include <libgeodecomp.h>
using namespace LibGeoDecomp;

class CollisionBody;

struct Collision {
  CollisionBody& other;
  //relative position of collision;
  FloatCoord<3> pos;
};

#endif // !COLLISION_HEADER
