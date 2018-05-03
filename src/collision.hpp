#include "collisionBody.hpp"
template<class Shape>
struct Collision {
  CollisionBody<Shape>& other;
  //relative position of collision;
  FloatCoord<3> pos;
}