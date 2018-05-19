#include "composedSpheresCB.hpp"

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

void ComposedSpheresCB::addVelocity(const FloatCoord<3>& addDeltaV)
{
    deltaV += addDeltaV;
}
