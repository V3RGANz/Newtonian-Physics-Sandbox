#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP

#include <libgeodecomp.h>
#include <list>
#include <string>
#include "collision.hpp"
#include "cell.hpp"
#include "tensor.hpp"

using namespace LibGeoDecomp;

/**
 * 3x3 matrix  
 */

//typename <class Shape>
class CollisionBody
{
public:
    virtual void update(const NPScell &hood, const int nanostep) = 0;

    virtual void detectCollision(CollisionBody &cBody) const = 0;

    virtual void resolveCollision(Collision &collision) = 0;

    virtual bool wasConsidered() const = 0;

    virtual FloatCoord<3> getPosition() const = 0;

    virtual FloatCoord<3> getVelocity() const = 0;

    virtual FloatCoord<3> getAcceleration() const = 0;

    virtual double getMass() const = 0;

    virtual Matrix<3, 3> getOrientation() const = 0;

    virtual AngularVTensor<3, 3> getAngVelocity() const = 0;

    virtual InertialTensor<3, 3> getInertialTensor() const = 0;

    virtual void addVelocity(const FloatCoord<3>&) = 0;

    virtual std::string toPOV() const = 0;

    friend std::ostream &operator<<(std::ostream &, const CollisionBody &);
};

std::ostream &operator<<(std::ostream &os, const CollisionBody &cb)
{
    os << cb.toPOV();
}

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP