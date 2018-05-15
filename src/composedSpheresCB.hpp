#ifndef NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP

#include "collisionBody.hpp"
#include "shape.hpp"

class ComposedSpheresCB : public CollisionBody
{
public:

private:
  std::list<SphereShape> spheres;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP