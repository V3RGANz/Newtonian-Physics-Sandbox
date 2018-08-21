#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP
#include "physics/bounding/boundingSphere.hpp"
#include "collision.hpp"


class CollisionDetection
{
public:
    //TODO: general case not implemented
    template<class body1, class body2>
    bool detectCollision(body1 &first, const body2 &second)
    {
        return false;
    };

    inline FloatCoord<3> getFirstCollision()
    {
        return body1CollisionPoint;
    }

    inline FloatCoord<3> getSecondCollision()
    {
        return body2CollisionPoint;
    }

private:
    FloatCoord<3> body1CollisionPoint;
    FloatCoord<3> body2CollisionPoint;
};

template<>
bool CollisionDetection::
detectCollision<BoundingSphere, BoundingSphere>(BoundingSphere &first, const BoundingSphere &second)
{
    FloatCoord<3> relativeVector = (first.getPosition() - second.getPosition());
    if (relativeVector.length() == 0) {
        body1CollisionPoint = first.getPosition();
        body2CollisionPoint = first.getPosition();
        return true;
    }
    else if (relativeVector.length() < first.getRadius() + second.getRadius()) {
        body1CollisionPoint = relativeVector * (first.getRadius()
            / relativeVector.length()); // maybe better use relativeVector - other.radius?
        body2CollisionPoint = -relativeVector * (second.getRadius() / relativeVector.length());
        return true;
    }
    return false;
}

// TODO: general spec
template<>
bool
CollisionDetection::
detectCollision<BoundingObject, BoundingObject>(BoundingObject &first, const BoundingObject &second)
{
    return false;
}

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP