#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP

#include <list>
#include <libgeodecomp.h>
#include "boundingObject.hpp"
#include "collisionDetection.hpp"

using namespace LibGeoDecomp;

/**
 * hierarchically included bounding objects. For localizing collisions
 * @tparam BoundingObject
 */
template<class BoundingObject>
class BoundingObjectTree
{
public:
    BoundingObject& getBoundingObject(){
        return boundingObject;
    }
    const std::list<BoundingObjectTree<BoundingObject> >& getChildren() const {
        return nodes;
    }
private:
    BoundingObject boundingObject;
    std::list<BoundingObjectTree<BoundingObject> > nodes;
};

template<>
class BoundingObjectTree<BoundingSphere>
{
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP