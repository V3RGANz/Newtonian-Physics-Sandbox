#ifndef BOUNDING_SPHERE_HEADER
#define BOUNDING_SPHERE_HEADER

#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere {
public:
  FloatCoord<3> getLastCollision() {
    return lastCollision;
  }

  const FloatCoord<3> getOtherCollision() const {
    return otherCollision;
  }

  void updatePosition(FloatCoord<3> externalBodyPos) {
    position = attachmentPoint + externalBodyPos;
  }

  // FIXME : always false in general case
  template<class boundingObj>
  bool detectCollision(boundingObj &other) {
    return false;
  }

private:
  double radius;
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
  FloatCoord<3> lastCollision;
  FloatCoord<3> otherCollision;
//  Collision lastCollision;
};

template<>
bool BoundingSphere::detectCollision<BoundingSphere>(BoundingSphere &other) {
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

#endif // !BOUNDING_SPHERE_HEADER
