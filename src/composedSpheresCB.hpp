#ifndef COMPOSEDSPHERES_CB_HEADER
#define COMPOSEDSPHERES_CB_HEADER

#include "collisionBody.hpp"

template<class Shape>
class ComposedSpheresCB : public CollisionBody<Shape>
{
  private:
    std::list<Shape> spheres;
};

#endif // !COMPOSEDSPHERES_CB_HEADER