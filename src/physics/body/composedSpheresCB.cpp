#include "composedSpheresCB.hpp"
#include "physics/collision/collisionTreeDetection.hpp"
#include "physics/collision/collisionResolve.hpp"
#include <cmath>

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
    << povRayTexture
    <<
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

namespace
{
bool collisionDetection(const ComposedSpheresCB::Sphere &first, const ComposedSpheresCB::Sphere &second)
{
    FloatCoord<3> relativeVector = (first.pos - second.pos);
    FloatCoord<3> body1CollisionPoint;
    FloatCoord<3> body2CollisionPoint;

    if (relativeVector.length() == 0) {
        body1CollisionPoint = first.pos;
        body2CollisionPoint = first.pos;
        return true;
    }
    else if (relativeVector.length() < first.radius + second.radius) {
        body1CollisionPoint = relativeVector * (first.radius
            / relativeVector.length()); // maybe better use relativeVector - other.radius?
        body2CollisionPoint = -relativeVector * (second.radius / relativeVector.length());
        return true;
    }
    return false;
}
}

//FIXME Collision not allows copying so currentCollisions commented
void ComposedSpheresCB::detectCollision(const ComposedSpheresCB &cBody)
{
    if (position == cBody.getPos())
        return;
    std::cout << "detecting collision...: pos1: " << position << " pos2: " << cBody.position << "\n";
    if (collisionDetection(spheres.back(), cBody.spheres.back())) {
        Collision current = {*this, cBody, position - cBody.position, cBody.position - position};
        CollisionResolve collisionResolve(current);
    }
//    CollisionTreeDetection<BoundingSphere, BoundingSphere> collisionTreeDetection(boundingObjectTree,
//                                                  cBody.getBoundingObjectTree());
//    collisionTreeDetection.search(position, cBody.getPos());
//
//    while (collisionTreeDetection.hasUnhandledCollisions()){
//        Collision current = collisionTreeDetection.getNextCollision(*this, cBody);
//        CollisionResolve collisionResolve(current);
////        currentCollisions.push_back(collisionTreeDetection.getNextCollision(*this, cBody));
//    }
}
const BoundingObjectTree<BoundingSphere>& ComposedSpheresCB::getBoundingObjectTree() const
{
    return boundingObjectTree;
}
FloatCoord<3> ComposedSpheresCB::getPos() const
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
CollisionBody *ComposedSpheresCB::copy() const
{
    auto * cp = new ComposedSpheresCB(spheres);
    cp->angularVelocity = angularVelocity;
    cp->velocity = velocity;
    cp->position = position;
    cp->boundingObjectTree = boundingObjectTree;
    cp->inertialTensor = inertialTensor;
    cp->orientation = orientation;
    cp->mass = mass;
    cp->myAABB = myAABB;
    return cp;
}
void ComposedSpheresCB::rotate(FloatCoord<3> rotationVector)
{
    Matrix<3, 3> rotationX(FloatCoord<3>(1, cos(rotationVector[0]), cos(rotationVector[0])));
    rotationX[1][2] = -sin(rotationVector[0]);
    rotationX[2][1] = sin(rotationVector[0]);

    Matrix<3, 3> rotationY(FloatCoord<3>(cos(rotationVector[1]), 1, cos(rotationVector[1])));
    rotationY[0][2] = -sin(rotationVector[1]);
    rotationY[2][0] = sin(rotationVector[1]);

    Matrix<3, 3> rotationZ(FloatCoord<3>(cos(rotationVector[2]), cos(rotationVector[2]), 1));
    rotationZ[0][1] = -sin(rotationVector[2]);
    rotationZ[1][0] = sin(rotationVector[2]);
    orientation *= rotationX * rotationY * rotationZ;
}

void ComposedSpheresCB::setVelocity(FloatCoord<3> velocityVector)
{
    velocity = velocityVector;
}
void ComposedSpheresCB::setPosition(FloatCoord<3> position)
{
    spheres.back().pos = position;
    this->position = position;
}
//ComposedSpheresCB &ComposedSpheresCB::operator=(const ComposedSpheresCB &other)
//{
//    angularVelocity     = other.angularVelocity;
//    velocity            = other.velocity;
//    position            = other.position;
//    boundingObjectTree  = other.boundingObjectTree;
//    inertialTensor      = other.inertialTensor;
//    orientation         = other.orientation;
//    mass                = other.mass;
//    myAABB              = other.myAABB;
//    acceleration        = other.acceleration;
//    spheres             = other.spheres;
//    return *this;
//}
//ComposedSpheresCB &ComposedSpheresCB::operator=(ComposedSpheresCB &&other) noexcept
//{
//    angularVelocity     = other.angularVelocity;
//    velocity            = other.velocity;
//    position            = other.position;
//    boundingObjectTree  = other.boundingObjectTree;
//    inertialTensor      = other.inertialTensor;
//    orientation         = other.orientation;
//    mass                = other.mass;
//    myAABB              = other.myAABB;
//    acceleration        = other.acceleration;
//    spheres             = std::move(other.spheres);
//    return *this;
//}
ComposedSpheresCB::ComposedSpheresCB(const ComposedSpheresCB &other)
    : angularVelocity(other.angularVelocity),
      velocity(other.velocity),
      position(other.position),
      boundingObjectTree(other.boundingObjectTree),
      inertialTensor(other.inertialTensor),
      orientation(other.orientation),
      mass(other.mass),
      myAABB(other.myAABB),
      acceleration(other.acceleration),
      spheres(other.spheres),
      povRayTexture(other.povRayTexture)
{}
ComposedSpheresCB::ComposedSpheresCB(const std::list<ComposedSpheresCB::Sphere> &spheres, double density)
    : spheres(spheres)
{
    boundingObjectTree.setBoundingObject(BoundingSphere(spheres.back().radius, FloatCoord<3>(0)));
    boundingObjectTree.getBoundingObject().updatePosition(spheres.back().pos);
    //FIXME: Just a sphere case
    InertiaTensor<3, 3>(FloatCoord<3>(2.0 / 5 * mass * spheres.back().radius * spheres.back().radius));
    position = spheres.back().pos;
    computeMass(density);
}
ComposedSpheresCB::ComposedSpheresCB(double density)
{
    computeMass(density);
}
void ComposedSpheresCB::setTexture(const POVRayTexture &texture)
{
    povRayTexture = texture;
}
void ComposedSpheresCB::setAngularVelocity(const AngularVTensor<3, 3> &tensor)
{
    angularVelocity = tensor;
}
