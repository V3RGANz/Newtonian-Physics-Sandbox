#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP

#include <libgeodecomp.h>
#include <list>
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
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDING_OBJECT_HPP
