#include "boundingSphere.hpp"
#include "collision.hpp"


class CollisionDetection {
public:
  template<class shape1, class shape2>
  bool detectCollision(shape1& first, shape2& second){
    //FIXME: general case not implemented
  }

  FloatCoord<3> getFirstCollision(){
    return shape1CollisionPoint;
  }

  FloatCoord<3> getSecondCollision(){
    return shape2CollisionPoint;
  }

private:
  FloatCoord<3> shape1CollisionPoint;
  FloatCoord<3> shape2CollisionPoint;
};

template<>
CollisionDetection::detectCollision<BoundingSphere, BoundingSphere>(BoundingSphere1&, BoundingSphere2&){
  FloatCoord<3> relativeVector = (BoundingSphere1.position - BoundingSphere2.position);
  if (relativeVector.length() < radius + other.radius) {
    shape1CollisionPoint = relativeVector * (radius / relativeVector.length()); // maybe better use relativeVector - other.radius?
    shape2CollisionPoint = -relativeVector * (other.radius / relativeVector.length());
    return true;
  }
  return false;
}

