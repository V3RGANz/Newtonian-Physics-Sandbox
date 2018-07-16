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



class NPSWorld
{
public:

    class BodiesGroup
    {
    public:
        void setVelocity(const FloatCoord<3> &velocity);

        void setAngularVelocity(const AngularVTensor<3, 3> &velocity);

        void rotate(FloatCoord<3> rotationVector);

        void movePosition(FloatCoord<3> shift);

        void setTexture(const POVRayTexture &);

        friend class NPSWorld;

    private:

        void addBody(ComposedSpheresCB *collisionBody);

        void splice(BodiesGroup &other);

        void removeBody(ComposedSpheresCB *collisionBody);

        std::set<ComposedSpheresCB *> bodies;
    };

    NPSWorld() = default;

    void addBody(const std::string &name, const ComposedSpheresCB &collisionBody);

    void addToGroup(const std::string &groupName, const ComposedSpheresCB &collisionBody);

    void addToGroup(const std::string &bodyName, const std::string &groupName, const ComposedSpheresCB &collisionBody);

    void changeBodyGroup(const std::string &bodyName, const std::string &groupName);

    void changeGroupName(const std::string &oldName, const std::string &newName);

    void mergeGroups(const std::string &destinationName, const std::string &sourceName);

    BodiesGroup *getGroup(const std::string &groupName);

    void deleteGroup(const std::string &groupName);

    ComposedSpheresCB *getBody(const std::string &name);;

    NPSCam &getCamera();

    void start();

    void setWorldSize(const Coord<3> &size);
private:
    static constexpr int steps = 1000;
    void compareBox(const CollisionBody &body);

    //FIXME: HARDCODED
    NPSWriter *npsWriter = new NPSWriter("nps_sim", 50);
    FloatCoord<3> maxBoundingBox = FloatCoord<3>(0);
    std::map<std::string, ComposedSpheresCB> bodies;
    std::map<std::string, BodiesGroup*> bodiesGroups;
    std::map<std::string, BodiesGroup> Groups;
    NPSInitializer *npsInitializer = nullptr;
    Coord<3> size;
    int count = 0;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
