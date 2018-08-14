#ifndef NEWTONIAN_PHYSICS_SANDBOX_NPSIMPORTER_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_NPSIMPORTER_HPP


#include <string>
#include "physics/body/collisionBody.hpp"
#include "physics/body/composedSpheresCB.hpp"
class NPSImporter
{
public:
    virtual void import(std::string filepath) = 0;
    virtual std::list<ComposedSpheresCB> getObjects() = 0;
};

//TODO: set names for bodies to allow modify them
/**
 * This interface allows to load scene from .obj file. Ignores all except spheres
 */
class SimpleOBJSpheresImporter: public NPSImporter
{
public:
    /**
     * Load scene from .obj file. Ignores all except spheres
     * @param filepath path to .obj file
     */
    void import(std::string filepath) override;
private:
    std::list<ComposedSpheresCB> importedObjects;
public:
    std::list<ComposedSpheresCB> getObjects() override;
};


#endif //NEWTONIAN_PHYSICS_SANDBOX_NPSIMPORTER_HPP
