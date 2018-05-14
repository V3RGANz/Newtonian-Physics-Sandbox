#ifndef BOUNDING_OBJECT_TREE_HEADER
#define BOUNDING_OBJECT_TREE_HEADER

#include <list>
#include "boundingObject.hpp"
#include "collisionDetection.hpp"
using namespace LibGeoDecomp;

// TODO: need to make possible detect collisions between arbitrary objects
template <typename BoundingObject>
class BoundingObjectTree
{
public:
  FloatCoord<3> detectCollision(FloatCoord<3> externalBodyPos, BoundingObjectTree& otherBoundObjTree)
  {
    std::list<FloatCoord<3> > detected = head.traverse(externalBodyPos, otherBoundObjTree.head.nodes);
    collisionPoints.push_back(detected);
    //FIXME: Fix collision list with relative to other pos
    otherBoundObjTree.collisionPoints.push_back(detected);
  };

private:

  void recvCollisions(std::list<FloatCoord<3> > detectedCollisions){
    collisionPoints.push_back(detectedCollisions);
    for (auto& collision : collisionPoints) {
      collision = -collision;
    }
  }

  /**
   * The tree class itself 
   */
  struct Node 
  {
    // FIXME: maybe need to get rid of recursive algorithm
    /**
     * Localising and make simplier collision detection
     * 
     * Traversing the tree going down to those branches,
     * which was detected in collisions, with other's 
     * boundary tree's nodes
     * 
     * @param externalBodyPos current position of body-owner of tree
     * (need to update because of Nodes stores only relative to owner 
     * position)
     * 
     * @param otherBodyConsideringNodes bounding objects of other body,
     * with which collisions have to be searched
     * 
     * @return list of collisions inside of node's bounding object
     */
    std::list<FloatCoord<3> > traverse(FloatCoord<3> externalBodyPos, std::list<Node> otherBodyConsideringNodes) {
      localCollisionPoints.clear();
      boundingObject.updatePosition(externalBodyPos);
      for (Node& otherNode : otherBodyConsideringNodes)
      {
        CollisionDetection collisionDetection;
        if (collisionDetection.detectCollision<BoundingObject, BoundingObject>(boundingObject, otherNode.boundingObject)) {
          if (nodes.empty()) {
            localCollisionPoints.push_back(boundingObject.getLastCollision());
          }
          for (auto &node : nodes) {
            localCollisionPoints.push_back(node.traverse(externalBodyPos, otherNode.nodes));
          }
        }
      }
      return localCollisionPoints;
    }
    std::list<FloatCoord<3> > localCollisionPoints;
    BoundingObject boundingObject;
    std::list<Node> nodes;
//    std::list<Node&> detectedNodes;
  };
  std::list<FloatCoord<3> > collisionPoints;
  Node head;
};


template <>
class BoundingObjectTree<BoundingSphere>
{
};

#endif // !BOUNDING_OBJECT_TREE_HEADER