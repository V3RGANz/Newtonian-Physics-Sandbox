#ifndef NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP

#include "collisionBody.hpp"
#include "shape.hpp"

class ComposedSpheresCB: public CollisionBody
{
public:

    std::string toPOV() const override;

    void addVelocity(const FloatCoord<3>& addDeltaV) override;

    inline
    void applyVelocity(void)
    {
        velocity += deltaV;
        deltaV = FloatCoord<3>(0);
    }

    inline
    void applyAngularVelocity(void)
    {
        angularVelocity += deltaW;
        deltaW = AngularVTensor<3, 3>(0);
    }
private:

    struct Sphere
    {
        Sphere(FloatCoord<3> pos, double radius)
            : pos(pos), radius(radius)
        {}

        FloatCoord<3> pos;
        double radius;
    };

    FloatCoord<3>           position        = FloatCoord<3>(0);
    FloatCoord<3>           velocity        = FloatCoord<3>(0);
    FloatCoord<3>           acceleration    = FloatCoord<3>(0);
    AngularVTensor<3, 3>    angularVelocity = AngularVTensor<3, 3>(0);
    InertialTensor<3, 3>    inertialTensor  = InertialTensor<3, 3>(0);
//    AngularVTensor<3, 3> angularAcceleration = 0;
    FloatCoord<3> deltaV;
    AngularVTensor<3, 3> deltaW;
    std::list<Sphere> spheres;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP