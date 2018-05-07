#ifndef BOUNDING_OBJECT_TREE_HEADER
#define BOUNDING_OBJECT_TREE_HEADER

#include <list>
#include "boundingObject.hpp"
using namespace LibGeoDecomp;

template <typename BoundingObject>
class BoundingObjectTree
{
public:
  FloatCoord<3> detectCollision(FloatCoord<3> externalBodyPos, BoundingObjectTree& otherBoundObjTree)
  {
    std::list<Collision> detected = head.traverse(externalBodyPos, otherBoundObjTree.head);
    collisionPoints.push_back(detected);
    //WARNING: Fix collosion list with relative to other pbj
    otherBoundObjTree.push_back(detected);
  }

private:

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
    std::list<Collision> traverse(FloatCoord<3> externalBodyPos, std::list<Node&> otherBodyConsideringNodes) {
      localCollisionPoints.clear();
      boundingObject.updatePosition(externalBodyPos);
      for (Node& otherNode : otherBodyConsideringNodes)
      if (boundingObject.detectCollision(otherBodyConsideringNodes)) {
        if (nodes.empty()) {
          localCollisionPoints.push_back(boundingObject.getLastCollision());
        }
        for (auto &node : nodes) {
          localCollisionPoints.push_back(node.traverse(externalBodyPos, otherNode.nodes));
        }
      }
      return localCollisionPoints
    }
    std::list<Collision> localCollisionPoints;
    BoundingObject boundingObject;
    std::list<Node> nodes;
    std::list<Node&> detectedNodes;
  };
  std::list<Collision > collisionPoints;
  Node head;
};

#endif // !BOUNDING_OBJECT_TREE_HEADER