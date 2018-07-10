#include "npsworld.hpp"
void NPSWorld::start()
{
    for (auto &body : bodies) {
        compareBox(body.second);
    }

    if (size == Coord<3>(0)) {
        size = Coord<3>(maxBoundingBox + FloatCoord<3>(1, 1, 1)) * 2;
    }
    else if (maxBoundingBox < size) {
        std::cout << "World size is too small. "
                     "Try to don't change it, "
                     "then it will be calculated automatically.\n";
        std::cout << "current : " << size
                  << "required no smaller than: "
                  << maxBoundingBox << std::endl;
        return;
    }

    std::cout << "world size: " << size;
    npsInitializer = new NPSInitializer(size, steps);

    for (auto &group : Groups) {
        for (auto &body : group.second.bodies) {
            npsInitializer->addCollisionBody(*body);
        }
    }

//    for (auto &pair : bodies) {
//        npsInitializer->addCollisionBody(pair.second);
//    }

    SerialSimulator<NPSCell> sim(npsInitializer);
    sim.addWriter(npsWriter);
    sim.run();
}
NPSCam &NPSWorld::getCamera()
{
    return npsWriter->getCamera();
}
ComposedSpheresCB *NPSWorld::getBody(const std::string &name)
{
    std::map<std::string, ComposedSpheresCB>::iterator found;
    if ((found = bodies.find(name)) == bodies.end()) {
        return nullptr;
    }

    return &(*found).second;
}
void NPSWorld::addBody(const std::string &name, const ComposedSpheresCB &collisionBody)
{
    auto &body = bodies[name] = *new ComposedSpheresCB(collisionBody);
    auto &NPSGeneral = Groups["NPSGeneral"];
    bodiesGroups[name] = &NPSGeneral;
    NPSGeneral.addBody(&body);
}
void NPSWorld::compareBox(const CollisionBody &body)
{
    FloatCoord<3> axes = body.getAABB().getAxes();
    for (int i = 0; i < 3; i++) {
        double objectOcc = std::abs(axes[i]) + std::abs(body.getPos()[i]);
        maxBoundingBox[i] = objectOcc > maxBoundingBox[i] ? objectOcc : maxBoundingBox[i];
    }
}
void NPSWorld::changeBodyGroup(const std::string &bodyName, const std::string &groupName)
{
    if (bodies.find(bodyName) == bodies.end())
        return;
    auto body = &bodies[bodyName];
    bodiesGroups[bodyName]->removeBody(body);
    bodiesGroups[bodyName] = &Groups[groupName];
    Groups[groupName].addBody(body);
}
void NPSWorld::changeGroupName(const std::string &oldName, const std::string &newName)
{
    if (Groups.find(newName) != Groups.end())
        return;
    auto found = Groups.find(oldName);
    if (found == Groups.end())
        return;
    std::swap(Groups[newName], found->second);
    Groups.erase(found);
}
void NPSWorld::mergeGroups(const std::string &destinationName, const std::string &sourceName)
{
    auto destination = Groups.find(destinationName);
    auto source = Groups.find(sourceName);
    if (destination == Groups.end() || source == Groups.end())
        return;
    destination->second.splice(source->second);
    Groups.erase(source);
}
NPSWorld::BodiesGroup *NPSWorld::getGroup(const std::string &groupName)
{
    auto found = Groups.find(groupName);
    if (found != Groups.end())
        return &found->second;
    return nullptr;
}
void NPSWorld::deleteGroup(const std::string &groupName)
{
    auto found = Groups.find(groupName);
    if (found != Groups.end())
        Groups.erase(found);
}
void NPSWorld::addToGroup(const std::string &groupName, const ComposedSpheresCB &collisionBody)
{
    Groups[groupName].addBody(new ComposedSpheresCB(collisionBody));
}
void
NPSWorld::addToGroup(const std::string &bodyName, const std::string &groupName, const ComposedSpheresCB &collisionBody)
{
    auto &body = bodies[bodyName] = collisionBody;
    auto &group = Groups[groupName];
    bodiesGroups[bodyName] = &group;
    group.addBody(&body);
}
void NPSWorld::setWorldSize(const Coord<3> &size)
{
    NPSWorld::size = size;
}
void NPSWorld::BodiesGroup::addBody(ComposedSpheresCB *collisionBody)
{
    bodies.insert(collisionBody);
}
void NPSWorld::BodiesGroup::removeBody(ComposedSpheresCB *collisionBody)
{
    bodies.erase(collisionBody);
}
void NPSWorld::BodiesGroup::setVelocity(const FloatCoord<3> &velocity)
{
    for (auto &body : bodies) {
        body->setVelocity(velocity);
    }
}
void NPSWorld::BodiesGroup::setAngularVelocity(const AngularVTensor<3, 3> &velocity)
{
    for (auto &body : bodies) {
        body->setAngularVelocity(velocity);
    }
}
void NPSWorld::BodiesGroup::rotate(FloatCoord<3> rotationVector)
{
    for (auto &body : bodies) {
        body->rotate(rotationVector);
    }
}
void NPSWorld::BodiesGroup::movePosition(FloatCoord<3> shift)
{
    for (auto &body : bodies) {
        body->setPosition(body->getPos() + shift);
    }
}
void NPSWorld::BodiesGroup::setTexture(const POVRayTexture &texture)
{
    for (auto body : bodies)
        body->setTexture(texture);
}
void NPSWorld::BodiesGroup::splice(BodiesGroup &other)
{
    bodies.insert(other.bodies.begin(), other.bodies.end());
    other.bodies.clear();
}
