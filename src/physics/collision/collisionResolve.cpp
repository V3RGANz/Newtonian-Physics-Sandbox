#include "collisionResolve.hpp"

//FIXME: sphere case
CollisionResolve::CollisionResolve(Collision &collision)
{
    CollisionBody &cb1 = collision.first;
    const CollisionBody &cb2 = collision.second;

    std::cout << "collision resolve:\n";
    std::cout << "cb1 :" << cb1 << "\n";
    std::cout << "cb2 :" << cb2;

    auto pos1to2 = cb2.getPos() - cb1.getPos();
    auto pos2to1 = cb1.getPos() - cb2.getPos();

    auto distancetocollision = pos1to2 - pos1to2 / pos1to2.length() * cb2.getAABB().getAxes()[0] / 2;

    auto newPosition = cb1.getPos() + (distancetocollision - (distancetocollision / distancetocollision.length()) * (cb1.getAABB().getAxes()[0] / 2 + cb1.getAABB().getAxes()[0] * 0.005));

    FloatCoord<3> ftosVelocityProjection = pos1to2 * ((cb1.getVelocity() * pos1to2) / (pos1to2 * pos1to2));
    FloatCoord<3> stofVelocityProjection = pos2to1 * ((cb2.getVelocity() * pos2to1) / (pos2to1 * pos2to1));

    cb1.addVelocity((stofVelocityProjection - ftosVelocityProjection) * 2 * cb2.getMass() / (cb1.getMass() + cb2.getMass()));

    std::cout << "delta V = " << (stofVelocityProjection - ftosVelocityProjection) * 2 * cb2.getMass() << "\n";

    if ((stofVelocityProjection - ftosVelocityProjection)[0] < 0)
        cb1.setPosition(newPosition);

//    double res;
//    FloatCoord<3> contactVelocity;
//    FloatCoord<3> impulseMagnitude;
//    FloatCoord<3> N;
//    AngularVTensor<3, 3> I;
//
////    Matrix<3, 3> matrix= cb1.getOrientation() * (cb1.getInertialTensor().getInversed());
//    InertiaTensor<3, 3> I0 =
//        cb1.getOrientation() *
//        (cb1.getInertialTensor().getInversed()) *
//        (cb1.getOrientation().transpose());
//    AngularVTensor<3, 3> I1 =
//        cb2.getOrientation() *
//        (cb2.getInertialTensor().getInversed()) *
//        (cb2.getOrientation().transpose());
//
//    FloatCoord<3> numerator = N.crossProduct(-contactVelocity * (1 + res));
//    double denominator;
//    denominator =
//        (cb1.getMass() + cb2.getMass()) /
//            (cb1.getMass() * cb2.getMass()) +
//            N * (I * cb1.getPos().crossProduct(N)).crossProduct(cb1.getPos()) +
//            N * (I * cb2.getPos().crossProduct(N)).crossProduct(cb2.getPos());
//
//    impulseMagnitude = numerator / denominator;
//
//    // FIXME: double computing. Look proposal
//    cb1.addVelocity(impulseMagnitude / cb1.getMass());
//    cb1.addAngularVelocity(AngularVTensor<3, 3>(I0 * (cb2.getPos().crossProduct(impulseMagnitude))));
}
