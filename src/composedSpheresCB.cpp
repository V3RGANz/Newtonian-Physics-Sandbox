#include "composedSpheresCB.hpp"
#include "collisionTreeDetection.hpp"

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
    spheres.push_back({pos, radius});
}

void ComposedSpheresCB::addVelocity(const FloatCoord<3>& addDeltaV)
{
    deltaV += addDeltaV;
}

inline
void ComposedSpheresCB::applyVelocity(void)
{
    velocity += deltaV;
    deltaV = FloatCoord<3>(0);
}

inline
void ComposedSpheresCB::applyAngularVelocity(void)
{
    angularVelocity += deltaW;
    deltaW = AngularVTensor<3, 3>(0);
}

void ComposedSpheresCB::update(const NPScell &hood, const int nanostep)
{
    consideredCollisions.clear();
    for (const CollisionBody& collisionBody : hood){
        detectCollision(collisionBody);
    }

//    for ()
}


ComposedSpheresCB::~ComposedSpheresCB(){
    spheres.clear();
}
void ComposedSpheresCB::detectCollision(const CollisionBody &cBody)
{
    CollisionTreeDetection collisionTreeDetection(boundingObjectTree,
                                                  cBody.getBoundingObjectTree());
    collisionTreeDetection.search(position, cBody.getPosition());

    while (collisionTreeDetection.hasUnhandldedCollisions()){
        Collision collision = collisionTreeDetection.getNextCollision(*this, cBody);
    }
}
BoundingObjectTree<BoundingSphere> &ComposedSpheresCB::getBoundingObjectTree() const
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

AxisAlignedBoundingBox ComposedSpheresCB::getAABB()
{
    if (myAABB == AxisAlignedBoundingBox::EmptyAABB){
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
        return {{maxX - minX, maxY - minY, maxZ - minZ},
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
InertialTensor<3, 3> ComposedSpheresCB::getInertialTensor() const
{
    return inertialTensor;
}
