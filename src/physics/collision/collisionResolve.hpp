#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP

#include <cmath>
#include "collision.hpp"
#include "physics/body/collisionBody.hpp"

//TODO: calculate coefficient of restitution, velocity of contact, normal force,
//TODO: inertialTensor in world system of reference
//FIXME: seems that instanse of class is usless, maybe make this utility class
class CollisionResolve
{
public:
    explicit CollisionResolve(Collision &collision);
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
