#ifndef NPS_CELL_HEADER
#define NPS_CELL_HEADER
#include <list>
#include <libgeodecomp.h>

using namespace LibGeoDecomp;

class CollisionBody;

// there is a problem
typedef BoxCell<std::list<CollisionBody> > NPScell;

#endif // !NPS_CELL_HEADER