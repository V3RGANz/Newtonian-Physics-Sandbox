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
  if (relativeVector.length() < boundingSphere1.getRadius() + boundingSphere2.getRadius()) {
    body1CollisionPoint = relativeVector * (boundingSphere1.getRadius() / relativeVector.length()); // maybe better use relativeVector - other.radius?
    body2CollisionPoint = -relativeVector * (boundingSphere2.getRadius()/ relativeVector.length());
    return true;
  }
  return false;
}

// TODO: general spec
template<> bool
CollisionDetection::
detectCollision<BoundingObject, BoundingObject>(BoundingObject& boundingObject1, BoundingObject& boundingObject2){
  return false;
}
