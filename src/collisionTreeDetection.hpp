#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP

#include "boundingObjectTree.hpp"

/**
 * Explores the objects for collision using bounding object tree
 *
 * @tparam BoundingObject1 first considering bounding Object
 * @tparam BoundingObject2 second considering bounding Object
 */

template<class BoundingObject1, class BoundingObject2>
class CollisionTreeDetection
{
public:
    typedef BoundingObjectTree<BoundingObject1> BoundingObjectTree1;
    typedef BoundingObjectTree<BoundingObject2> BoundingObjectTree2;

    CollisionTreeDetection(BoundingObjectTree1 &boundingObjectTree1,
                           BoundingObjectTree2 &boundingObjectTree2)
        :
        boundingObjectTree1(boundingObjectTree1),
        boundingObjectTree2(boundingObjectTree2)
    {}

    /**
     * Searh collision between bounding objects;
     * @param externalBody1Pos current position of body-owner of first bounding object
     * @param externalBody2Pos current position of body-owner of second bounding object
     */
    void search(FloatCoord<3> externalBody1Pos, FloatCoord<3> externalBody2Pos){
        this->externalBody1Pos = externalBody1Pos;
        this->externalBody2Pos = externalBody2Pos;
    }

private:
    /**
     * Localising and make simpler collision detection
     * TODO: make more readable
     */
    void traverse(BoundingObjectTree1& boundingObjectTree11, BoundingObjectTree2& boundingObjectTree21)
    {
        CollisionDetection collisionDetection;
        if (collisionDetection.detectCollision(boundingObjectTree11.getBoundingObject(),
                                               boundingObjectTree21.getBoundingObject())) {
            if (boundingObjectTree11.getChildren().empty()) {
                if (boundingObjectTree21.getChildren().empty()) {
                    firstCollisionPoints.push_back(collisionDetection.getFirstCollision());
                    secondCollisionPoints.push_back(collisionDetection.getSecondCollision());
                    return;
                } else {
                    for(auto& child : boundingObjectTree21.getChildren()){
                        child.getBoundingObject().updatePosition(externalBody2Pos);
                        traverse(boundingObjectTree11, child);
                    }
                }
            } else if (boundingObjectTree21.getBoundingObject().getChildren().empty()) {
                for (auto& child : boundingObjectTree11.getChildren()){
                    child.getBoundingObject().updatePosition(externalBody1Pos);
                    traverse(child, boundingObjectTree21);
                }
            } else {
                for (auto& child1 : boundingObjectTree11.getChildren()){
                    for (auto& child2 : boundingObjectTree21.getChildren()) {
                        child1.getBoundingObject().updatePosition(externalBody1Pos);
                        child2.getBoundingObject().updatePosition(externalBody2Pos);
                        traverse(child1, child2);
                    }
                }
            }
        }
    }

    FloatCoord<3> externalBody1Pos;
    FloatCoord<3> externalBody2Pos;
    std::list<FloatCoord<3> > firstCollisionPoints;
    std::list<FloatCoord<3> > secondCollisionPoints;
    BoundingObjectTree<BoundingObject1> &boundingObjectTree1;
    BoundingObjectTree<BoundingObject2> &boundingObjectTree2;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
