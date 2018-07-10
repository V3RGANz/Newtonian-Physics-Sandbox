#include "initializer.hpp"
NPSInitializer::NPSInitializer(const Coord<3> &dimensions, unsigned steps)
    :
    SimpleInitializer<NPSCell>(dimensions, steps), dimensions(dimensions)
{}
void NPSInitializer::grid(GridBase<NPSCell, 3> *target)
{
    cellsFilling.clear();
//    static constexpr BOXSIZE =
    //FIXME : harcoded cell size
    CoordBox<3> box = target->boundingBox();
    for (CoordBox<3>::Iterator j = box.begin(); j != box.end(); ++j) {
        NPSCell npsCell(FloatCoord<3>(*j), FloatCoord<3>{1, 1, 1});
        target->set(*j, npsCell);
    }
    for (auto& collisionBody : collisionBodies){
        auto cell = target->get(Coord<3>(collisionBody.getPos()));
        cell.insert(collisionBody);
        target->set(Coord<3>(collisionBody.getPos()), cell);
        //        cellsFilling[Coord<3>(collisionBody.getPos())].insert(collisionBody);
    }
//    for (auto& pair : cellsFilling){
//        target->set(pair.first, pair.second);
//    }
}
void NPSInitializer::addCollisionBody(ComposedSpheresCB &collisionBody)
{
    collisionBodies.push_back(collisionBody);
}
