#include "boundingObject.hpp"

class BoundingSphere : public BoundingObject
{
public:
  virtual FloatCoord<3> getLastCollision() override;
  virtual void updatePosition(FloatCoord<3> externalBodyPos) override
  {
    position = attachmentPoint + externalBodyPos;
  }
  // FIXME : always false in general case
  template<class boundingObj>
  bool detectCollision(boundingObj& other){
    return false;
  }

private:
  
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
  FloatCoord<3> pos;
  double radius;
};

template<>
  bool BoundingSphere::detectCollision<BoundingSphere>(BoundingSphere& other){
    if ((pos - other.pos).length() < radius + other.radius) {
      return true;
    }
    return false;
  }
