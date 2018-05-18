#ifndef NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP

#include "collisionBody.hpp"
#include "shape.hpp"

class ComposedSpheresCB : public CollisionBody
{
public:

  std::string toPOV() const override {
    std::stringstream buf;
    for (const Sphere& sphere : spheres)
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
private:

  struct Sphere{
    Sphere(FloatCoord<3> pos, double radius) : pos(pos), radius(radius)
    {}

    FloatCoord<3> pos;
    double radius;
  };

  FloatCoord<3>     position            = 0;
  FloatCoord<3>     velocity            = 0;
  FloatCoord<3>     acceleration        = 0;
  AngularVTensor<3>         angularVelocity     = 0;
  AngularVTensor<3>         angularAcceleration = 0;


  FloatCoord<3>     deltaV;
  AngularVTensor<3>         deltaW;
  std::list<Sphere> spheres;
};

#endif // !NEWTONIAN_PHYSICS_SANDBOX_COMPOSEDSPHERESCB_HPP