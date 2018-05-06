#ifndef BOUNDING_SPHERE_HEADER
#define BOUNDING_SPHERE_HEADER

#include "boundingObject.hpp"
using namespace LibGeoDecomp;

class BoundingSphere : public BoundingObject
{
public:
  virtual FloatCoord<3> 
  getLastCollision() override
  {

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

  void writeCollison(FloatCoord<3> collision){
    lastCollision = collision;
  }

  double        radius;
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
  FloatCoord<3> lastCollision;
};

template<>
  bool BoundingSphere::detectCollision<BoundingSphere>(BoundingSphere& other){
    if ((position - other.position).length() < radius + other.radius) {
      return true;
    }
    return false;
  }

#endif // !BOUNDING_SPHERE_HEADER
