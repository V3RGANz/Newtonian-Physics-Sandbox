#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP

#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere: BoundingObject
{
public:

    BoundingSphere() = default;

    BoundingSphere(double radius, const FloatCoord<3> &attachmentPoint)
        : radius(radius), attachmentPoint(attachmentPoint)
    {
    }

    void updatePosition(FloatCoord<3> externalBodyPos) override
    {
        position = attachmentPoint + externalBodyPos;
    }

    inline FloatCoord<3> getPosition(void) const
    {
        return position;
    }

    inline double getRadius() const
    {
        return radius;
    }

private:
    double radius;
    FloatCoord<3> position;
    // relative location in Object's reference system
    FloatCoord<3> attachmentPoint;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP
