#include "collisionResolve.hpp"


CollisionResolve::CollisionResolve(Collision &collision)
{
    CollisionBody &cb1 = collision.first;
    const CollisionBody &cb2 = collision.second;

    double res;
    FloatCoord<3> contactVelocity;
    FloatCoord<3> impulseMagnitude;
    FloatCoord<3> N;
    AngularVTensor<3, 3> I;

    InertiaTensor<3, 3> I0 =
        cb1.getOrientation() *
        (cb1.getInertialTensor().getInversed()) *
        (cb1.getOrientation().transpose());
    AngularVTensor<3, 3> I1 =
        cb2.getOrientation() *
        (cb2.getInertialTensor().getInversed()) *
        (cb2.getOrientation().transpose());

    FloatCoord<3> numerator = N.crossProduct(-contactVelocity * (1 + res));
    double denominator;
    denominator =
        (cb1.getMass() + cb2.getMass()) /
            (cb1.getMass() * cb2.getMass()) +
            N * (I * cb1.getPos().crossProduct(N)).crossProduct(cb1.getPos()) +
            N * (I * cb2.getPos().crossProduct(N)).crossProduct(cb2.getPos());

    impulseMagnitude = numerator / denominator;

    // FIXME: double computing. Look proposal
    cb1.addVelocity(impulseMagnitude / cb1.getMass());
    cb1.addAngularVelocity(AngularVTensor<3, 3>(I0 * (cb2.getPos().crossProduct(impulseMagnitude))));
}