#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include <iostream>
#endif
#include "boundingSphere.hpp"
#include "collision.hpp"


class CollisionDetection
{
public:
    //TODO: general case not implemented
    template<class body1, class body2>
    bool detectCollision(body1 &first, const body2 &second)
    {
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
        std::cout << "using general spec\n";
#endif
        return false;
    };

    FloatCoord<3> getFirstCollision()
    {
        return body1CollisionPoint;
    }

    FloatCoord<3> getSecondCollision()
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

#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
    std::cout << "1st pos" << first.getPosition()
        << "\n2nd pos" << first.getPosition()
        << "\n1st radius" << first.getRadius()
        << "\n2nd radius" << first.getRadius()
        << "\nrelativeVector" << relativeVector
        << "\n";
#endif
    if (relativeVector.length() == 0){
        body1CollisionPoint = first.getPosition();
        body2CollisionPoint = first.getPosition();
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
        std::cout << "collisionDetected at " << body1CollisionPoint << std::endl;
#endif
        return true;
    }
    else if (relativeVector.length() < first.getRadius() + second.getRadius()) {
        body1CollisionPoint = relativeVector * (first.getRadius()
            / relativeVector.length()); // maybe better use relativeVector - other.radius?
        body2CollisionPoint = -relativeVector * (second.getRadius() / relativeVector.length());
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
        std::cout << "collisionDetected at " << body1CollisionPoint << std::endl;
#endif
        return true;
    }
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
    std::cout << "collision not detected between " << first.getPosition() << " and " << second.getPosition() << std::endl;
#endif
    return false;
}

// TODO: general spec
template<>
bool
CollisionDetection::
detectCollision<BoundingObject, BoundingObject>(BoundingObject &first, const BoundingObject &second)
{
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
    std::cout << "using BoundingObject spec\n";
#endif
    return false;
}

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONDETECTION_HPP