#ifndef NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP

#include <libgeodecomp.h>
#include "collisionBody.hpp"
#include "composedSpheresCB.hpp"
#include "Initializer.hpp"
//#include "writer.hpp"

//FIXME: HARDCODED
class NPSWorld
{
public:

    NPSWorld() = default;

    void addBody(ComposedSpheresCB& collisionBody){
        bodies.push_back(collisionBody);
    }

    void start(){
        for (auto& body : bodies){
            compareBox(body);
        }
        npsInitializer = new NPSInitializer(Coord<3>(maxBoundingBox + FloatCoord<3>(1,1,1)), steps);
        npsInitializer->addCollisionBody(bodies);
//        SerialSimulator<NPScell> sim(npsInitializer);
//        sim.addWriter(new NPSWriter("nps_sim", 200));
    }
private:
    static constexpr int steps = 1000;
    void compareBox(const CollisionBody& body) {
        FloatCoord<3> axes = body.getAABB().getAxes();
        for (int i = 0; i < 3; i++){
            maxBoundingBox[i] = axes[i] > maxBoundingBox[i] ? axes[i] : maxBoundingBox[i];
        }
    }

    FloatCoord<3> maxBoundingBox = FloatCoord<3>(0);
    std::list<ComposedSpheresCB> bodies;
    NPSInitializer* npsInitializer = nullptr;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
