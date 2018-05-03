#include <list>
#include "boundingObject.hpp"

template <typename BoundingObject>
class BoundingObjectTree
{
public:
  FloatCoord<3> detectCollision(FloatCoord<3> externalBodyPos)
  {
    head.traverse(externalBodyPos);
  }

private:
  struct Node
  {
    // FIXME: maybe need to get rid of recursive algorithm
    std::list<FloatCoord<3> > traverse(FloatCoord<3> externalBodyPos)
    {
      localCollisionPoints.clear();
      boundingObject.updatePosition(externalBodyPos);
      if (boundingObject)
      {
        // leaf reached
        if (nodes.empty())
        {
          localCollisionPoints.push_back(boundingObject.getLastCollision());
          return localCollisionPoints;
        } 
        for (auto &node : nodes)
        {
          localCollisionPoints.push_back(node.traverse());
        }
      } else {
        return localCollisionPoints; // empty list
      }
    }
    std::list<FloatCoord<3> > localCollisionPoints;
    BoundingObject boundingObject;
    std::list<Node> nodes;
  };
  std::list<FloatCoord<3> > collisionPoints;
  Node head;
};


template <>
class BoundingObjectTree<BoundingSphere>
{
};