#ifndef NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP


#include "Initializer.hpp"
class NPSWorld
{
public:
    void addBody(CollisionBody& collisionBody){

    }
private:
    struct Box {
        unsigned X;
        unsigned Y;
        unsigned Z;
    };
    Box maxBoundingBox = {0, 0, 0};
    NPSInitializer* npsInitializer;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
