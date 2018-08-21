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


/**
 * the main class of physical system
 * Through this interface user can add objects to system, combine them into groups,
 * modify groups or directly objects, modify camera and visualisation
 */
class NPSWorld
{
public:

    class BodiesGroup
    {
    public:
        /**
         * set velocity of all objects in the group
         * @param velocity new velocity value
         */
        void setVelocity(const FloatCoord<3> &velocity);

        /**
         * set angular velocity of all objects in the group
         * @param velocity new angular velocity value
         */
        void setAngularVelocity(const AngularVTensor<3, 3> &velocity);

        /**
         * rotate all objects in the group
         * @param rotationVector rotation vector
         */
        void rotate(FloatCoord<3> rotationVector);

        /**
         * shift position of all objects in group
         * @param shift shift value
         */
        void movePosition(FloatCoord<3> shift);

        /**
         * set texture of object
         * @param texture new texture
         */
        void setTexture(const POVRayTexture &texture);

        friend class NPSWorld;

    private:

        void addBody(ComposedSpheresCB *collisionBody);

        void splice(BodiesGroup &other);

        void removeBody(ComposedSpheresCB *collisionBody);

        std::set<ComposedSpheresCB *> bodies;
    };

    NPSWorld() = default;

    /**
     * add object to system
     * object is defined in the "NPSGeneral" group
     * @param name unic name for object
     * @param collisionBody object to add
     */
    void addBody(const std::string &name, const ComposedSpheresCB &collisionBody);

    /**
     * add object to system and defined in groupName group
     * @param groupName name of group to define
     * @param collisionBody object to add
     */
    void addToGroup(const std::string &groupName, const ComposedSpheresCB &collisionBody);

    /**
     * add object to system and defined in groupName group
     * @param bodyName unic name for object
     * @param groupName name of group to define
     * @param collisionBody object to add
     */
    void addToGroup(const std::string &bodyName, const std::string &groupName, const ComposedSpheresCB &collisionBody);

    /**
     * move object to other group
     * @param bodyName unic name of object
     * @param groupName name for another group
     */
    void changeBodyGroup(const std::string &bodyName, const std::string &groupName);

    /**
     * change name of group
     * @param oldName
     * @param newName
     */
    void changeGroupName(const std::string &oldName, const std::string &newName);

    /**
     * combine two groups into one
     * if at least one group is not found nothing to be happened
     * @param destinationName name of group to which to move sourceName
     * @param sourceName name of group which to move to destinationName
     */
    void mergeGroups(const std::string &destinationName, const std::string &sourceName);

    /**
     * get pointer to group by name
     * @param groupName name of the desired group
     * @return pointer to group if found, nullptr if not found
     */
    BodiesGroup *getGroup(const std::string &groupName);

    /**
     * remove all objects in group by name
     * @param groupName name of group to delete
     */
    void deleteGroup(const std::string &groupName);

    /**
     * get pointer to object by name
     * @param name name of object
     * @return pointer to object if found, nullptr if not found
     */
    ComposedSpheresCB *getBody(const std::string &name);;

    /**
     * get system camera
     * @return system camera reference
     */
    NPSCam &getCamera();

    /**
     * run the simulation
     */
    void start();

    /**
     * set cell size
     * @param size
     */
    void setCellSize(const Coord<3> &size);

    void setWorldSize(const Coord<3> &size);
private:
    static constexpr int steps = 2000;
    void compareBox(const CollisionBody &body);
    void compareWorldSize(const CollisionBody &body);

    //FIXME: HARDCODED
    NPSWriter *npsWriter = new NPSWriter("nps_sim", 50);
    FloatCoord<3> maxBoundingBox = FloatCoord<3>(0);
    std::map<std::string, ComposedSpheresCB> bodies;
    std::map<std::string, BodiesGroup*> bodiesGroups;
    std::map<std::string, BodiesGroup> Groups;
    NPSInitializer *npsInitializer = nullptr;
    Coord<3> cellSize = Coord<3>(0);
    Coord<3> worldSize = Coord<3>(0);
    int count = 0;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSWORLD_HPP
