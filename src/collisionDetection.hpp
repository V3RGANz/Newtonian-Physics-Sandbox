#include "boundingSphere.hpp"
#include "collision.hpp"


class CollisionDetection {
public:
  //TODO: general case not implemented
  template<class body1, class body2>
  bool detectCollision(body1& first, body2& second){
  }

  FloatCoord<3> getFirstCollision(){
    return body1CollisionPoint;
  }

  FloatCoord<3> getSecondCollision(){
    return body2CollisionPoint;
  }

private:
  FloatCoord<3> body1CollisionPoint;
  FloatCoord<3> body2CollisionPoint;
};

template<> bool CollisionDetection::
detectCollision<BoundingSphere, BoundingSphere>(BoundingSphere& boundingSphere1, BoundingSphere& boundingSphere2){
  FloatCoord<3> relativeVector = (boundingSphere1.getPosition() - boundingSphere2.getPosition());
  if (relativeVector.length() < radius + other.radius) {
    body1CollisionPoint = relativeVector * (radius / relativeVector.length()); // maybe better use relativeVector - other.radius?
    body2CollisionPoint = -relativeVector * (other.radius / relativeVector.length());
    return true;
  }
  return false;
}

// TODO: general spec
template<> bool
CollisionDetection::
detectCollision<BoundingObject, BoundingObject>(BoundingObject1& boundingObject1, BoundingObject2& boundingObject2){
  return false;
}
