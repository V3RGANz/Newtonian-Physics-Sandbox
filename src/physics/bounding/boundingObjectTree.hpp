#ifndef NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP

#include <list>
#include <libgeodecomp.h>
#include "boundingSphere.hpp"
#include "../../math/tensor.hpp"

using namespace LibGeoDecomp;

/**
 * hierarchically included bounding objects. For localizing collisions
 * @tparam BoundingObject
 */
template<class BoundingObject>
class BoundingObjectTree
{
public:
    BoundingObject& getBoundingObject() {
        return boundingObject;
    }

    const BoundingObject& getBoundingObject() const {
        return boundingObject;
    }

    const std::list<BoundingObjectTree<BoundingObject> >& getChildren() const {
        return nodes;
    }

    void updateBoundingsPositions(const FloatCoord<3>& externalBodyPos)
    {
        boundingObject.updatePosition(externalBodyPos);
        for (auto& node : nodes){
            node.updateBoundingsPositions(externalBodyPos);
        }
    }
private:
    BoundingObject boundingObject;
    std::list<BoundingObjectTree<BoundingObject> > nodes;
};

template<>
class BoundingObjectTree<BoundingSphere>
{
public:

    BoundingObjectTree() = default;

    BoundingObjectTree(FloatCoord<3> center, double radius) : boundingObject(radius, center)
    {
    }

    explicit BoundingObjectTree(std::list<BoundingObjectTree<BoundingSphere> > nodes) : nodes(std::move(nodes))
    {
    }

    void setBoundingObject(const BoundingSphere &boundingObject)
    {
        BoundingObjectTree::boundingObject = boundingObject;
    }

    BoundingSphere& getBoundingObject() {
        return boundingObject;
    }

    const BoundingSphere& getBoundingObject() const {
        return boundingObject;
    }

    std::list<BoundingObjectTree<BoundingSphere> >& getChildren() {
        return nodes;
    }

    const std::list<BoundingObjectTree<BoundingSphere> >& getChildren() const {
        return nodes;
    }

    void updateBoundingsPositions(const FloatCoord<3>& externalBodyPos)
    {
        boundingObject.updatePosition(externalBodyPos);
        for (auto& node : nodes)
            node.updateBoundingsPositions(externalBodyPos);
    }
    void rotate(AngularVTensor<3, 3> dW)
    {
        for (auto& node : nodes)
            node.rotate(dW);
    }
private:
    BoundingSphere boundingObject;
    std::list<BoundingObjectTree<BoundingSphere> > nodes;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_BOUNDINGOBJECTTREE_HPP