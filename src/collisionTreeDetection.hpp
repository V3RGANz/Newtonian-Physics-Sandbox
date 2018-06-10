#ifndef NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP

#include "boundingObjectTree.hpp"
#include "collisionDetection.hpp"
#include "composedSpheresCB.hpp"

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
                           const BoundingObjectTree2 &boundingObjectTree2)
        :
        boundingObjectTree1(boundingObjectTree1),
        boundingObjectTree2(boundingObjectTree2)
    {}

    /**
     * Search collision between bounding objects;
     * @param externalBody1Pos current position of body-owner of first bounding object
     * @param externalBody2Pos current position of body-owner of second bounding object
     */
    void search(FloatCoord<3> externalBody1Pos, FloatCoord<3> externalBody2Pos)
    {
        this->externalBody1Pos = externalBody1Pos;
        this->externalBody2Pos = externalBody2Pos;

        traverse(boundingObjectTree1, boundingObjectTree2);
    }

    bool hasUnhandledCollisions(void)
    {
        return !firstCollisionPoints.empty();
    }

    Collision getNextCollision(CollisionBody &first, const CollisionBody &second)
    {
        FloatCoord<3> pos1to2 = firstCollisionPoints.back();
        FloatCoord<3> pos2to1 = secondCollisionPoints.back();
        firstCollisionPoints.pop_back();
        secondCollisionPoints.pop_back();
        return {first, second, pos1to2, pos2to1};
    }

private:
    /**
     * Localising and make simpler collision detection
     * TODO: make more readable
     */
    void traverse(BoundingObjectTree1 &boundingObjectTree11, const BoundingObjectTree2 &boundingObjectTree21)
    {
        CollisionDetection collisionDetection;
        if (collisionDetection
            .detectCollision<BoundingObject1, BoundingObject2>(boundingObjectTree11.getBoundingObject(),
                                                               boundingObjectTree21.getBoundingObject())) {
            if (boundingObjectTree11.getChildren().empty()) {
                if (boundingObjectTree21.getChildren().empty()) {
                    firstCollisionPoints.push_back(collisionDetection.getFirstCollision());
                    secondCollisionPoints.push_back(collisionDetection.getSecondCollision());
                    return;
                }
                else {
                    for (auto &child : boundingObjectTree21.getChildren()) {
                        //FIXME: should update somehow
//                        child.getBoundingObject().updatePosition(externalBody2Pos);
                        traverseSingleFirst(boundingObjectTree11.getBoundingObject(), child);
                    }
                }
            }
            else if (boundingObjectTree21.getChildren().empty()) {
                for (auto &child : boundingObjectTree11.getChildren()) {
                    //FIXME: should update somehow
//                    child.getBoundingObject().updatePosition(externalBody1Pos);
                    traverseSingleSecond(child, boundingObjectTree21.getBoundingObject());
                }
            }
            else {
                for (auto &child1 : boundingObjectTree11.getChildren()) {
                    for (auto &child2 : boundingObjectTree21.getChildren()) {
                        //FIXME: should update somehow
//                        child1.getBoundingObject().updatePosition(externalBody1Pos);
                        //FIXME: should update somehow
//                        child2.getBoundingObject().updatePosition(externalBody2Pos);
                        traverse(child1, child2);
                    }
                }
            }
        }
    }

    /*
     * if first bounding object is leaf
     * TODO: make more readable
     */
    void traverseSingleFirst(BoundingObject1 &boundingObject1, const BoundingObjectTree2 &boundingObjectTree21)
    {
        CollisionDetection collisionDetection;
        if (collisionDetection.detectCollision<BoundingObject1, BoundingObject2>(boundingObject1,
                                                                                 boundingObjectTree21
                                                                                     .getBoundingObject())) {
            if (boundingObjectTree21.getChildren().empty()) {
                firstCollisionPoints.push_back(collisionDetection.getFirstCollision());
                secondCollisionPoints.push_back(collisionDetection.getSecondCollision());
                return;
            }
            else {
                for (auto &child : boundingObjectTree21.getChildren()) {
                    //FIXME: should update somehow
//                    child.getBoundingObject().updatePosition(externalBody2Pos);
                    traverseSingleFirst(boundingObject1, child);
                }
            }
        }
    }

    /*
     * if second bounding object is leaf
     * TODO: make more readable
     */
    void traverseSingleSecond(BoundingObjectTree1 &boundingObjectTree11, const BoundingObject2 &boundingObject2)
    {
        CollisionDetection collisionDetection;
        if (collisionDetection.detectCollision<BoundingObject1, BoundingObject2>
            (boundingObjectTree11.getBoundingObject(), boundingObject2)) {
            if (boundingObjectTree11.getChildren().empty()) {
                firstCollisionPoints.push_back(collisionDetection.getFirstCollision());
                secondCollisionPoints.push_back(collisionDetection.getSecondCollision());
                return;
            }
            else {
                for (auto &child : boundingObjectTree11.getChildren()) {
                    //FIXME: should update somehow
//                    child.getBoundingObject().updatePosition(externalBody2Pos);
                    traverseSingleSecond(child, boundingObject2);
                }
            }
        }
    }

    FloatCoord<3> externalBody1Pos;
    FloatCoord<3> externalBody2Pos;
    std::list<FloatCoord<3> > firstCollisionPoints;
    std::list<FloatCoord<3> > secondCollisionPoints;
    BoundingObjectTree<BoundingObject1> &boundingObjectTree1;
    const BoundingObjectTree<BoundingObject2> &boundingObjectTree2;
};

#endif //!NEWTONIAN_PHYSICS_SANDBOX_COLLISIONTREEDETECTION_HPP
