#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP

#include <cmath>
#include "collision.hpp"
#include "collisionBody.hpp"

//TODO: calculate coefficient of restitution, velocity of contact, normal force,
//TODO: inertialTensor in world system of reference
class CollisionResolve {
public:
  CollisionResolve(Collision& collision){
    CollisionBody& cbodies[2] = {collision.first,
                                 collision.second};

    double  res;
    FloatCoord<3> contactVelocity;
    FloatCoord<3> impulseMagnitude;
    FloatCoord<3> N;
    AngularVTensor<3> I;
    AngularVTensor<3> I0 = cbodies[0].getOrientation() * I;
    AngularVTensor<3> I1;

    FloatCoord<3> numerator = crossProduct(N,- contactVelocity * (1 + res));
    double denominator;
    denominator = (cbodies[0].getMass() + cbodies[1].getMass()) /
                  (cbodies[0].getMass() * cbodies[1].getMass()) +
            N * (I * cbodies[0].getPosition().crossProduct(N)).crossProduct(cbodies[0]) +
            N * (I * cbodies[1].getPosition().crossProduct(N)).crossProduct(cbodies[1]) +
                   N * crossProduct(I * crossProduct(cbodies[0].getPosition(), N), cbodies[0]);

    impulseMagnitude = numerator / denominator;
//    cbodies[0].
  }
private:

  inline
  FloatCoord<3> crossProduct(const FloatCoord<3>& u,const FloatCoord<3>& v) const {
    return FloatCoord<3>(u[2]*v[3] - u[3]*v[2],
                         u[3]*v[1] - u[1]*v[3],
                         u[1]*v[2] - u[2]*v[1]);
  }

  FloatCoord<3> impulseMagnitude;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONRESOLVE_HPP
