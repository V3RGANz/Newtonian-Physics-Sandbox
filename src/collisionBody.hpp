#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP

#include <libgeodecomp.h>
#include <list>
#include <string>
#include "boundingObjectTree.hpp"
#include "collision.hpp"
#include "cell.hpp"
#include "tensor.hpp"
#include "boundingSphere.hpp"
#include "axisalignedboundingbox.hpp"

using namespace LibGeoDecomp;

class CollisionBody
{
public:
    typedef MyAPI API;

    //FIXME: HARDCODED
//    static constexpr double DELTA_T = 0.1;

    virtual void update(const NPScell &hood, const int nanostep) = 0;

    virtual void detectCollision(const CollisionBody &cBody) = 0;

    virtual void resolveCollision(Collision &collision) = 0;

    virtual bool wasConsidered() const = 0;

    virtual FloatCoord<3> getPosition() const = 0;

    virtual FloatCoord<3> getVelocity() const = 0;

    virtual FloatCoord<3> getAcceleration() const = 0;

    virtual const BoundingObjectTree<BoundingSphere>& getBoundingObjectTree() const = 0;

    virtual double getMass() const = 0;

    virtual AxisAlignedBoundingBox getAABB() const = 0;

    virtual Matrix<3, 3> getOrientation() const = 0;

    virtual AngularVTensor<3, 3> getAngVelocity() const = 0;

    virtual InertiaTensor<3, 3> getInertialTensor() const = 0;

    virtual void addVelocity(const FloatCoord<3>&) = 0;

    virtual void addAngularVelocity(const AngularVTensor<3, 3>&) = 0;

    virtual std::string toPOV() const = 0;

    virtual void getCollison(CollisionBody& me) const = 0;

    virtual CollisionBody* copy() const = 0;

    //FIXME: should be pure
    virtual ~CollisionBody() = default;

    friend std::ostream &operator<<(std::ostream &, const CollisionBody &);
};

std::ostream &operator<<(std::ostream &os, const CollisionBody &cb);

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COLLISIONBODY_HPP