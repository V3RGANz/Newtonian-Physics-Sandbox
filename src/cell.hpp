#ifndef NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP
#include <list>
#include <libgeodecomp.h>

using namespace LibGeoDecomp;

class CollisionBody;
class ComposedSpheresCB;

// FIXME: there is a problem
//typedef BoxCell<std::list<CollisionBody*> > NPScell;

class MyAPI :
    public APITraits::HasCubeTopology<3>,
    public APITraits::HasStencil<Stencils::Moore<3, 1> >,
    public APITraits::HasNanoSteps<2>
{};

//TODO: cell with arbitrary CollisionBody
class NPScell : public BoxCell<std::list<ComposedSpheresCB> >
{
public:
    typedef MyAPI API;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_CELL_HPP