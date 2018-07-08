#ifndef NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#include <list>
#include <libgeodecomp.h>
#include "physics/body/composedSpheresCB.hpp"
//#include <ntphyssbox.hpp>

using namespace LibGeoDecomp;

// FIXME: there is a problem
//typedef BoxCell<std::list<CollisionBody*> > NPSCell;
//TODO: cell with arbitrary CollisionBody
//FIXME: vector is not good, but std::list missing operator<< (need for BoxCell::insert() method)
//class NPSCell : public BoxCell<std::vector<ComposedSpheresCB> >
//{
//public:
//    typedef MyAPI API;
//};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP