#ifndef SHAPE_HEADER
#define SHAPE_HEADER

// #include<tuple>

#include <libgeodecomp.h>
#include "physics/collision/collision.hpp"
using namespace LibGeoDecomp;


// FIX ME: useless on that stage

class SphereShape
{
    template<class OtherShape>
    bool detectCollision(OtherShape &otherShape)
    {
        // FIXME: there should be general specialization
    }
    FloatCoord<3> getLastCollision()
    {
        return lastCollision;
    }
    FloatCoord<3> getOtherLastCollision()
    {
        return othupdateerCollision;
    }

private:
    double radius;
    FloatCoord<3> lastCollision;
    FloatCoord<3> otherCollision;
    //  template<class OtherShape>
//  void writeCollision(Collision collision){
//    lastCollision = collision;
//  }
    FloatCoord<3> position;
};

template<>
bool SphereShape::detectCollision<SphereShape>(SphereShape &other)
{
    FloatCoord<3> relativeVector = (other.position - position);
    if (relativeVector.length() < radius + other.radius) {
//      lastCollision = {
//                        other,
//                        relativeVector * (radius / relativeVector.length())
//                      };
        lastCollision = relativeVector * (radius / relativeVector.length()); // maybe better use just relativeVector ?
        otherCollision = -relativeVector * (other.radius / relativeVector.length());
        return true;
    }
    return false;
}

#endif // !SHAPE_HEADER
