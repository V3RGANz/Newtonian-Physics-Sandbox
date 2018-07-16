#include "collisionResolve.hpp"

//FIXME: sphere case
CollisionResolve::CollisionResolve(Collision &collision)
{
    CollisionBody &cb1 = collision.first;
    const CollisionBody &cb2 = collision.second;

    double radius1 = cb1.getAABB().getAxes()[0] / 2;
    double radius2 = cb2.getAABB().getAxes()[0] / 2;

    FloatCoord<3> pos1to2 = cb2.getPos() - cb1.getPos();
    FloatCoord<3> pos2to1 = cb1.getPos() - cb2.getPos();

    collision.pos1to2 = cb1.getPos() + (pos1to2 / pos1to2.length()) * radius1;
    collision.pos2to1 = cb2.getPos() + (pos2to1 / pos2to1.length()) * radius2;

    double res = 1;
    double impulseMagnitude;
    FloatCoord<3> N = pos1to2 / pos1to2.length();
    double contactVelocity = N * (cb1.getVelocity() - cb2.getVelocity());
    AngularVTensor<3, 3> I;

    InertiaTensor<3, 3> invInTr0 = cb1.getInertialTensor();
    invInTr0.inverse();
    InertiaTensor<3, 3> invInTr1 = cb1.getInertialTensor();
    invInTr1.inverse();

    InertiaTensor<3, 3> I0 =
        cb1.getOrientation() *
            invInTr0 *
        (cb1.getOrientation().transpose());
    InertiaTensor<3, 3> I1 =
        cb2.getOrientation() *
            invInTr1 *
        (cb2.getOrientation().transpose());

//    std::cout << "cb1.orientation = \n" << cb1.getOrientation() << "\n";
//    std::cout << "cb1.InTr = \n" << cb1.getInertialTensor() << "\n";
//    std::cout << "cb2.InTr = \n" << cb2.getInertialTensor() << "\n";
//    std::cout << "cb1.invInTr = \n" << invInTr0 << "\n";
//    std::cout << "cb1.orientation^(-1) = \n" << (cb1.getOrientation().transpose()) << "\n";
//    std::cout << "I0 = \n" << I0 << "\n";
//    std::cout << "I1 = \n" << I1 << "\n";
//    std::cout << "all preparation calculation made.\n";

    double numerator = -contactVelocity * (1 + res);
    double denominator =
        cb1.getInvMass() + cb2.getInvMass();// +
//            N * (I0 * collision.pos1to2.crossProduct(N)).crossProduct(collision.pos1to2) +
//            N * (I1 * collision.pos2to1.crossProduct(N)).crossProduct(collision.pos2to1);

    impulseMagnitude = numerator / denominator;
    FloatCoord<3> impulse = N * impulseMagnitude;
    // FIXME: double computing. Look proposal
    cb1.addVelocity(impulse / cb1.getMass());
    cb1.addAngularVelocity(AngularVTensor<3, 3>(I0 * (cb2.getPos().crossProduct(impulse))));
}
