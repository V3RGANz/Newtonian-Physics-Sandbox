#ifndef BOUNDING_OBJECT_HEADER
#define BOUNDING_OBJECT_HEADER

#include <libgeodecomp.h>
#include <list>
using namespace LibGeoDecomp;

class BoundingObject
{
public:
  // need to be used if collision with outer bounding objects was detected
  virtual void updatePosition(FloatCoord<3> externalBodyPos);
};

#endif // !BOUNDING_OBJECT_HEADER
