#ifndef SHAPE_HEADER
#define SHAPE_HEADER

#include <libgeodecomp.h>
#include "collision.hpp"
using namespace LibGeoDecomp;


// FIX ME: useless on that stage

class Shape {
  virtual bool detectCollision(Shape& other);
  virtual Collision<Shape> getLastCollision();
};

class Sphere : public Shape {
  template<class OtherShape>
  bool detectCollision(OtherShape& otherShape){
    // FIXME: there should be general specialization
  }
  virtual Collision<Shape> getLastCollision() override{
  }

private:
  double radius;
  Collision<Shape> lastCollision;
  template<class OtherShape>
  void writeCollison(Collision<OtherShape> collision){
    lastCollision = collision;
  }
  FloatCoord<3> position;
};

template<>
bool Sphere::detectCollision<Sphere>(Sphere& other){
  FloatCoord<3> relativeVector = (position - other.position);
    if (relativeVector.length() < radius + other.radius) 
    {
      lastCollision = { 
                        other, 
                        relativeVector * (radius / relativeVector.length())
                      };
      otherCollisionPos = lastCollision - relativeVector;
      other.writeCollison({*this, otherCollisionPos});
      return true;
    }
    return false;
}

#endif // !SHAPE_HEADER
