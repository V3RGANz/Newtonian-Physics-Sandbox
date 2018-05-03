#include "boundingObject.hpp"

class BoundingSphere : public BoundingObject
{
public:
  virtual FloatCoord<3> getLastCollision() override
  {
    
  }
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

  void writeCollison(FloatCoord<3> collision){
    lastCollision = collision;
  }

  double        radius;
  FloatCoord<3> position;
  // relative location in Object's reference system
  FloatCoord<3> attachmentPoint;
  FloatCoord<3> pos;
  FloatCoord<3> lastCollision;
};

template<>
  bool BoundingSphere::detectCollision<BoundingSphere>(BoundingSphere& other){
    FloatCoord<3> relativeVector = (pos - other.pos);
    if (relativeVector.length() < radius + other.radius) {
      lastCollision = relativeVector * (radius / relativeVector.length());
      otherCollison = lastCollision - relativeVector;
      other.writeCollison(otherCollision);
      return true;
    }
    return false;
  }
