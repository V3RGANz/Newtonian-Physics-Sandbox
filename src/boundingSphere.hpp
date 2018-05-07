#ifndef BOUNDING_SPHERE_HEADER
#define BOUNDING_SPHERE_HEADER
#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collision.hpp"

using namespace LibGeoDecomp;

class BoundingSphere : public BoundingObject
{
public:
  virtual Collision
  getLastCollision() override
  {
    return lastCollision;
  }
  virtual void 
  updatePosition(FloatCoord<3> externalBodyPos) override
  {
    position = attachmentPoint + externalBodyPos;
  }
  
  // FIXME : always false in general case
  template<class boundingObj>
  bool detectCollision(boundingObj& other){
    return false;
  }

private:

  double        radius;
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
  Collision lastCollision;
};

template<>
  bool BoundingSphere::detectCollision<BoundingSphere>(BoundingSphere& other){
      FloatCoord<3> relativeVector = (position - other.position);
    if (relativeVector.length() < radius + other.radius) 
    {
      lastCollision = { 
                        other, 
                        relativeVector * (radius / relativeVector.length())
                      };
      return true;
    }
    return false;
  }

#endif // !BOUNDING_SPHERE_HEADER
