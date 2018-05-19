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
    CollisionResolve(Collision &collision)
    {
        CollisionBody& cb1 = collision.first;
        CollisionBody& cb2 = collision.second;

        double res;
        FloatCoord<3> contactVelocity;
        FloatCoord<3> impulseMagnitude;
        FloatCoord<3> N;
        AngularVTensor<3, 3> I;
        //FIXME
        InertialTensor<3, 3> I0 =
            cb1.getOrientation() *
            cb1.getInertialTensor().getInversed() *
            cb1.getOrientation().transpose();
        AngularVTensor<3, 3> I1;

        FloatCoord<3> numerator = N.crossProduct(-contactVelocity * (1 + res));
        double denominator;
        denominator =
            (cb1.getMass() + cb2.getMass()) /
            (cb1.getMass() * cb2.getMass()) +
             N * (I * cb1.getPosition().crossProduct(N)).crossProduct(cb1.getPosition()) +
             N * (I * cb2.getPosition().crossProduct(N)).crossProduct(cb2.getPosition());

        impulseMagnitude = numerator / denominator;
//    cbodies[0].
    }
private:

    FloatCoord<3> impulseMagnitude;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
