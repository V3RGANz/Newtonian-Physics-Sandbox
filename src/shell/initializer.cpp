#include "initializer.hpp"
NPSInitializer::NPSInitializer(const Coord<3> &dimensions, unsigned steps)
    :
    SimpleInitializer<NPSCell>(dimensions, steps)
{}
void NPSInitializer::grid(GridBase<NPSCell, 3> *target)
{
    CoordBox<3> box = target->boundingBox();
    std::cout << "collisionBodies.size()" << collisionBodies.size() << "\n";
    for (auto& collisionBody : collisionBodies){
        cellsFilling[Coord<3>(collisionBody.getPos())].insert(collisionBody);
    }
    for (auto& pair : cellsFilling){
        target->set(pair.first, pair.second);
    }
}
void NPSInitializer::addCollisionBody(ComposedSpheresCB &collisionBody)
{
    collisionBodies.push_back(collisionBody);
}
