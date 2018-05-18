#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP

#include "boundingObjectTree.hpp"


// TODO: this class shall fix problem described in boundingObjectTree.hpp

template<class BoundingObject1, class BoundingObject2>
class CollisionTreeDetection
{
public:
    CollisionTreeDetection(BoundingObjectTree<BoundingObject1> &boundingObjectTree1,
                           BoundingObjectTree<BoundingObject2> &boundingObjectTree2)
        :
        boundingObjectTree1(boundingObjectTree1),
        boundingObjectTree2(boundingObjectTree2)
    {}

    void traverse(FloatCoord<3> externalBody1Pos, FloatCoord<3> externalBody2Pos)
    {
//    boundingObjectTree1.detectCollision()
    }

private:
    BoundingObjectTree<BoundingObject1> &boundingObjectTree1;
    BoundingObjectTree<BoundingObject2> &boundingObjectTree2;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
