#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP

#include <libgeodecomp.h>
#include <list>
#include "math/tensor.hpp"
using namespace LibGeoDecomp;

/**
 * Bounding object need to discard deliberately impossible collisions,
 * because it much simpler for considering
 */
class BoundingObject
{
public:
    // need to be used if collision with outer bounding objects was detected
    virtual void updatePosition(FloatCoord<3> externalBodyPos) = 0;
    virtual FloatCoord<3> getPosition() const = 0;
    virtual void rotate(AngularVTensor<3, 3> dW) = 0;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP
