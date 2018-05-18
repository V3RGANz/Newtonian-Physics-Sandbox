#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP

#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere: BoundingObject
{
public:

    virtual void updatePosition(FloatCoord<3> externalBodyPos)
    {
        position = attachmentPoint + externalBodyPos;
    }

    inline FloatCoord<3> getPosition(void)
    {
        return position;
    }

    inline double getRadius()
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
