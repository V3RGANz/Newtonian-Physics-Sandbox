#include <libgeodecomp.h>
#include <list>

class BoundingObject
{
public:
  virtual FloatCoord<3> getLastCollision();
  // need to be used if collision with outer bounding objects was detected
  virtual void updatePosition(FloatCoord<3> externalBodyPos);
  // template<class boundingObj>
  virtual bool detectCollision(BoundingObject& other);
};