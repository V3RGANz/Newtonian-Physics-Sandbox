#ifndef COLLISION_BODY_HEADER
#define COLLISION_BODY_HEADER

#include <libgeodecomp.h>
#include <list>
#include "collision.hpp"
#include "cell.hpp"
using namespace LibGeoDecomp;

/**
 * 3x3 matrix  
 */
class Tensor
{
};



template<class Shape>
class CollisionBody
{
  public:
    typedef Shape myShape;
    
    virtual void update(const NPScell& hood, const int nanostep);

    virtual void detectCollision(CollisionBody &cBody) = delete;
    virtual void resolveCollision(Collision& collision) = delete;
    virtual bool wasConsidered() = delete;
    virtual FloatCoord<3> getPosition() = delete;
    virtual FloatCoord<3> getVelocity() = delete;
    virtual FloatCoord<3> getAcceleration() = delete;
    virtual double getMass() = delete;
    virtual Tensor getOrientation() = delete;
    virtual Tensor getAngVelocity() = delete;
};

#endif // !COLLISION_BODY_HEADER