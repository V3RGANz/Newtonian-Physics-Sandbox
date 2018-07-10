#ifndef NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP

#include <list>
#include <map>
#include "physics/body/composedSpheresCB.hpp"

//TODO should import from Blender
class NPSInitializer : public SimpleInitializer<NPSCell>
{
public:

    NPSInitializer(const Coord<3>& dimensions, unsigned steps);

    void grid(GridBase<NPSCell, 3>* target) override;

    void addCollisionBody(ComposedSpheresCB& collisionBody);

//    inline void addCollisionBody(std::list<ComposedSpheresCB>& container){
//        collisionBodies.splice(collisionBodies.end(), container);
//    }


    template <class Container>
    inline void addCollisionBody(Container& container){
        for (auto& collisionBody : container) {
            collisionBodies.push_back(collisionBody);
        }
    }

private:
    Coord<3> dimensions;
    std::map<Coord<3>, NPSCell > cellsFilling;
    std::vector<ComposedSpheresCB> collisionBodies;
};
//
//template <>
//inline void NPSInitializer::addCollisionBody<std::list<ComposedSpheresCB> >(std::list<ComposedSpheresCB>& container){
//    collisionBodies.splice(collisionBodies.end(), container);
//}

/**
 * Starting point for every simulation.
 * Initializer take objects and their initial
 * condition from user data
 */

//
//class NPSSimulator // wrapper over LGD Simulator and Initializer actually
//{
//public:
//    NPSSimulator() = default;
//    // TODO: dimensions should be calculated automatically, steps should not be hardcoded
//    explicit NPSSimulator(Coord<3>& dimensions) : npsInitializer(dimensions, 100000)
//    {
//
//    }
//
//    inline
//    void addCollisionBody(CollisionBody& collisionBody) {
//        npsInitializer.addCollisionBody(collisionBody);
//    }
//private:
//};









#endif //!NEWTONIAN_PHYSICS_SANDBOX_INITIALIZER_HPP
