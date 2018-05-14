#ifndef BOUNDING_SPHERE_HEADER
#define BOUNDING_SPHERE_HEADER

#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere : BoundingObject{
public:

  virtual void updatePosition(FloatCoord<3> externalBodyPos) override{
    position = attachmentPoint + externalBodyPos;
  }

  inline FloatCoord<3> getPosition (void) {
    return position;
  }

private:
  double radius;
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
};

#endif // !BOUNDING_SPHERE_HEADER
