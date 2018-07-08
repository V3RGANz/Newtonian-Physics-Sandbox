#ifndef NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP

#include <string>
#include <map>

#include <libgeodecomp.h>
#include "physics/body/collisionBody.hpp"
#include "physics/body/composedSpheresCB.hpp"
#include "initializer.hpp"
#include "writer.hpp"
//#include "writer.hpp"

//FIXME: HARDCODED
class NPSWorld
{
public:

    NPSWorld() = default;

    void addBody(const std::string &name, const ComposedSpheresCB& collisionBody);

    ComposedSpheresCB* getBody (const std::string &name);;

    NPSCam& getCamera();

    void start();
private:
    static constexpr int steps = 1000;
    void compareBox(const CollisionBody& body);

    NPSWriter* npsWriter = new NPSWriter("nps_sim", 200);
    FloatCoord<3> maxBoundingBox = FloatCoord<3>(0);
    std::map<std::string, ComposedSpheresCB> bodies;
    NPSInitializer* npsInitializer = nullptr;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
