#include <libgeodecomp.h>

class Shape {
  virtual bool detectCollision(Shape& other);
};

class Sphere : public Shape {
  template<class OtherShape>
  bool detectCollision(OtherShape& otherShape){
    // FIXME: there should be general specialization
  }
private:
  double radius;
  FloatCoord<3> position;  
};

template<>
bool Sphere::detectCollision<Sphere>(Sphere& otherShape){
  if (radius + otherShape.radius > (position - otherShape.position).length()){
    return true;
  }
  return false;
}