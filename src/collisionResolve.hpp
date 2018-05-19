#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP

#include <cmath>
#include "collision.hpp"
#include "collisionBody.hpp"

//TODO: calculate coefficient of restitution, velocity of contact, normal force,
//TODO: inertialTensor in world system of reference
class CollisionResolve
{
public:
    CollisionResolve(Collision &collision);
private:
    FloatCoord<3> impulseMagnitude;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
