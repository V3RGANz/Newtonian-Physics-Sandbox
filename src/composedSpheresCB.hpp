#ifndef COMPOSEDSPHERES_CB_HEADER
#define COMPOSEDSPHERES_CB_HEADER

#include "collisionBody.hpp"
#include "shape.hpp"

class ComposedSpheresCB : public CollisionBody
{
public:

private:
  std::list<SphereShape> spheres;
};

#endif // !COMPOSEDSPHERES_CB_HEADER