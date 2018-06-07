#ifndef NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP

#include <list>
#include <map>
#include "cell.hpp"
#include "collisionBody.hpp"

//TODO should import from Blender
class NPSInitializer : public SimpleInitializer<NPScell>
{
public:

    NPSInitializer(const Coord<3>& dimensions, unsigned steps) :
        SimpleInitializer<NPScell>(dimensions, steps)
    {}

    virtual void grid(GridBase<NPScell, 3>* target)
    {
        CoordBox<3> box = target->boundingBox();
        for (auto& collisionBody : collisionBodies){
            cellsFilling[Coord<3>(collisionBody.getPosition())] << collisionBody;
        }
        for (auto& pair : cellsFilling){
            target->set(pair.first, pair.second);
        }
    }

    inline
    void addCollisionBody(CollisionBody& collisionBody)
    {
        collisionBodies.push_back(collisionBody);
    }

    template <class Container<CollisionBody> >
    inline void addCollisionBody(Container<CollisionBody&>& container){
        for (auto& collisionBody : container) {
            collisionBodies.push_back(collisionBody);
        }
    }

private:
    std::map<Coord<3>, NPScell > cellsFilling;
    std::list<CollisionBody&> collisionBodies;
};

template <>
inline void NPSInitializer::addCollisionBody<std::list<CollisionBody&> >(std::list<CollisionBody&>& container){
    collisionBodies.splice(collisionBodies.end(), container);
}

/**
 * Starting point for every simulation.
 * Initializer take objects and their initial
 * condition from user data
 */

class NPSSimulator // wrapper over LGD Simulator and Initializer actually
{
public:
    NPSSimulator() = default;
    // TODO: dimensions should be calculated automatically, steps should not be hardcoded
    NPSSimulator(Coord<3>& dimensions) : npsInitializer(dimensions, 100000)
    {

    }

    inline
    void addCollisionBody(CollisionBody& collisionBody) {
        npsInitializer.addCollisionBody(collisionBody);
    }
private:
    NPSInitializer npsInitializer;
};









#endif //!NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
