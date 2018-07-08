#include "npsworld.hpp"
void NPSWorld::start()
{
    for (auto& body : bodies) {
        compareBox(body.second);
    }
    npsInitializer = new NPSInitializer(Coord<3>(maxBoundingBox + FloatCoord<3>(1,1,1)), steps);

    std::cout << "bodies.size() = " << bodies.size() << "\n";
    for (auto& pair : bodies) {
        npsInitializer->addCollisionBody(pair.second);
    }

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
    bodies[name] = collisionBody;
}
void NPSWorld::compareBox(const CollisionBody &body)
{
    FloatCoord<3> axes = body.getAABB().getAxes();
    for (int i = 0; i < 3; i++) {
        maxBoundingBox[i] = axes[i] > maxBoundingBox[i] ? axes[i] : maxBoundingBox[i];
    }
}
