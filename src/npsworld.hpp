#ifndef NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP

#include <string>
#include <map>

#include <libgeodecomp.h>
#include "collisionBody.hpp"
#include "composedSpheresCB.hpp"
#include "Initializer.hpp"
#include "writer.hpp"
//#include "writer.hpp"

//FIXME: HARDCODED
class NPSWorld
{
public:

    NPSWorld() = default;

    void addBody(const std::string &name, const ComposedSpheresCB& collisionBody){
        bodies[name] =  collisionBody;
    }

    ComposedSpheresCB* getBody (const std::string &name) {
        std::map<std::string, ComposedSpheresCB>::iterator found;
        if ((found = bodies.find(name)) == bodies.end()) {
            return nullptr;
        }

        return &(*found).second;
    };

    void start(){
        for (auto& body : bodies) {
            compareBox(body.second);
        }
        npsInitializer = new NPSInitializer(Coord<3>(maxBoundingBox + FloatCoord<3>(1,1,1)), steps);

        for (auto& pair : bodies) {
            npsInitializer->addCollisionBody(pair.second);
        }

        SerialSimulator<NPSCell> sim(npsInitializer);
        sim.addWriter(new NPSWriter("nps_sim", 200));
        sim.run();
    }
private:
    static constexpr int steps = 1000;
    void compareBox(const CollisionBody& body) {
        FloatCoord<3> axes = body.getAABB().getAxes();
        for (int i = 0; i < 3; i++) {
            maxBoundingBox[i] = axes[i] > maxBoundingBox[i] ? axes[i] : maxBoundingBox[i];
        }
    }

    FloatCoord<3> maxBoundingBox = FloatCoord<3>(0);
    std::map<std::string, ComposedSpheresCB> bodies;
    NPSInitializer* npsInitializer = nullptr;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
