#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP

#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "physics/collision/collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere: BoundingObject
{
public:

    BoundingSphere() = default;

    BoundingSphere(double radius, const FloatCoord<3> &attachmentPoint);

    void updatePosition(FloatCoord<3> externalBodyPos) override;

    FloatCoord<3> getPosition(void) const;

    double getRadius() const;

private:
    double radius = 0;
    FloatCoord<3> position = FloatCoord<3>(0);
    // relative location in Object's reference system
    FloatCoord<3> attachmentPoint = FloatCoord<3>(0);
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGSPHERE_HPP
