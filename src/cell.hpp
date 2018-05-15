#ifndef NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#include <list>
#include <libgeodecomp.h>

using namespace LibGeoDecomp;

class CollisionBody;

// FIXME: there is a problem
typedef BoxCell<std::list<CollisionBody> > NPScell;

#endif // !NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP