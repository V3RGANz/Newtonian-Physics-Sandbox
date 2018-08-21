#include "initializer.hpp"
NPSInitializer::NPSInitializer(const Coord<3> &dimensions, unsigned steps, const Coord<3>& cellSize)
    :
    SimpleInitializer<NPSCell>(dimensions, steps), dimensions(dimensions), cellSize(cellSize)
{}
void NPSInitializer::grid(GridBase<NPSCell, 3> *target)
{
    cellsFilling.clear();
//    static constexpr BOXSIZE =
    //FIXME : harcoded cell cellSize
    CoordBox<3> box = target->boundingBox();
    for (CoordBox<3>::Iterator j = box.begin(); j != box.end(); ++j) {
        Coord<3> origin(Coord<3>(*j)[0] * cellSize[0],
                        Coord<3>(*j)[1] * cellSize[1],
                        Coord<3>(*j)[2] * cellSize[2]);
        auto dims = FloatCoord<3>(cellSize);
        NPSCell npsCell(FloatCoord<3>(origin), dims);
        target->set(*j, npsCell);
    }
    for (auto& collisionBody : collisionBodies){
        auto bodyPos = FloatCoord<3>(collisionBody.getPos());
        bodyPos[0] /= cellSize[0];
        bodyPos[1] /= cellSize[1];
        bodyPos[2] /= cellSize[2];
        auto coordinate = Coord<3>(bodyPos);
        auto cell = target->get(coordinate);
        cell.insert(collisionBody);
        target->set(coordinate, cell);
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
