#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include <iostream>
#endif
#include "composedSpheresCB.hpp"
#include "collisionTreeDetection.hpp"
#include "collisionResolve.hpp"

std::string ComposedSpheresCB::toPOV() const
{
    std::stringstream buf;
    for (const Sphere &sphere : spheres)
    buf <<
    "sphere {\n"
    "  <"
    << sphere.pos[0] << ", "
    << sphere.pos[1] << ", "
    << sphere.pos[2] << ">, "
    << sphere.radius << "\n"
    <<
    "  texture {\n"
    "    pigment {color White}\n"
    "    finish {phong 0.9 metallic}\n"
    "  }\n"
    "}\n";

    return buf.str();
}

void ComposedSpheresCB::addSphere(FloatCoord<3> pos, double radius)
{
    spheres.emplace_back(pos, radius);
}

void ComposedSpheresCB::addVelocity(const FloatCoord<3>& addDeltaV)
{
    deltaV += addDeltaV;
}

void ComposedSpheresCB::update(const NPScell &hood, const int nanostep)
{
//    consideredCollisions.clear();
    boundingObjectTree.updateBoundingsPositions(position);
    for (const CollisionBody& collisionBody : hood){
        detectCollision(collisionBody);
    }

    for (auto& collision : currentCollisions){
        CollisionResolve collisionResolve(collision);
    }

    applyVelocity();
    applyAngularVelocity();
}


//ComposedSpheresCB::~ComposedSpheresCB(){
//    spheres.clear();
//}
void ComposedSpheresCB::detectCollision(const CollisionBody &cBody)
{
#ifdef NEWTONIAN_PHYSICS_SANDBOX_DEBUG
    std::cout << "detectCollision()\n";
#endif
    //FIXME
    CollisionTreeDetection<BoundingSphere, BoundingSphere> collisionTreeDetection(boundingObjectTree,
                                                  cBody.getBoundingObjectTree());
    collisionTreeDetection.search(position, cBody.getPosition());

    while (collisionTreeDetection.hasUnhandledCollisions()){
        currentCollisions.push_back(collisionTreeDetection.getNextCollision(*this, cBody));
    }
}
const BoundingObjectTree<BoundingSphere>& ComposedSpheresCB::getBoundingObjectTree() const
{
    return boundingObjectTree;
}
FloatCoord<3> ComposedSpheresCB::getPosition() const
{
    return position;
}
FloatCoord<3> ComposedSpheresCB::getVelocity() const
{
    return velocity;
}
FloatCoord<3> ComposedSpheresCB::getAcceleration() const
{
    return acceleration;
}
double ComposedSpheresCB::getMass() const
{
    return mass;
}

AxisAlignedBoundingBox ComposedSpheresCB::getAABB() const
{
    if (myAABB.empty()){
        if (spheres.empty()){
            return myAABB;
        }
        double minX = spheres.front().pos[0];
        double minY = spheres.front().pos[1];
        double minZ = spheres.front().pos[2];
        double maxX = spheres.front().pos[0];
        double maxY = spheres.front().pos[1];
        double maxZ = spheres.front().pos[2];
        for (auto& sphere: spheres) {
            if (sphere.pos[0] - sphere.radius < minX)
                minX = sphere.pos[0] - sphere.radius;
            if (sphere.pos[1] - sphere.radius < minY)
                minY = sphere.pos[1] - sphere.radius;
            if (sphere.pos[2] - sphere.radius < minZ)
                minZ = sphere.pos[2] - sphere.radius;
            if (sphere.pos[0] + sphere.radius > maxX)
                maxX = sphere.pos[0] + sphere.radius ;
            if (sphere.pos[1] + sphere.radius > maxY)
                maxY = sphere.pos[1] + sphere.radius ;
            if (sphere.pos[2] + sphere.radius > maxZ)
                maxZ = sphere.pos[2] + sphere.radius ;
        }
        return {FloatCoord<3>(maxX - minX, maxY - minY, maxZ - minZ),
                FloatCoord<3>(0),
                position - FloatCoord<3>(minX, minY, minZ)};
    } else {
        return myAABB;
    }
}

//TODO
bool ComposedSpheresCB::wasConsidered() const
{
    return false;
}

//FIXME: useless maybe
void ComposedSpheresCB::resolveCollision(Collision &collision)
{

}
Matrix<3, 3> ComposedSpheresCB::getOrientation() const
{
    return orientation;
}
AngularVTensor<3, 3> ComposedSpheresCB::getAngVelocity() const
{
    return angularVelocity;
}
InertiaTensor<3, 3> ComposedSpheresCB::getInertialTensor() const
{
    return inertialTensor;
}
void ComposedSpheresCB::getCollison(CollisionBody &me) const
{
}
void ComposedSpheresCB::addAngularVelocity(const AngularVTensor<3, 3> &tensor)
{
    angularVelocity += tensor;
}
