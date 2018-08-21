#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include "shell/npsworld.hpp"
#include "physics/body/composedSpheresCB.hpp"
#include "physics/collision/collisionResolve.hpp"

int main()
{
    ComposedSpheresCB spheres[5] = {
        ComposedSpheresCB{{
             {FloatCoord<3>(1,0,0), 0.5}
        }},
        ComposedSpheresCB{{
             {FloatCoord<3>(4,0,0), 0.5}
        }},
        ComposedSpheresCB{{
             {FloatCoord<3>(5,0,0), 0.5}
        }},
        ComposedSpheresCB{{
             {FloatCoord<3>(6,0,0), 0.5}
        }},
        ComposedSpheresCB{{
             {FloatCoord<3>(7,0,0), 0.5}
        }}
    };

    POVRayTexture texture;
    texture.setPigment(POVRayColor::Aquamarine);

    NPSWorld npsWorld;

    for (int i = 0; i < 5; ++i) {
        npsWorld.addBody("sphere" + std::to_string(i), spheres[i]);
    }

//    npsWorld.addBody("sphere0", spheres[0]);
//    npsWorld.addBody("sphere2", spheres[1]);
//    npsWorld.addBody("sphere4", spheres[4]);

    npsWorld.changeBodyGroup("sphere0", "active");
    npsWorld.changeBodyGroup("sphere4", "active");
    npsWorld.getGroup("active")->setTexture(texture);
    npsWorld.getBody("sphere0")->setVelocity(FloatCoord<3>(0.02, 0, 0));
    std::cout << "started\n";
    npsWorld.start();

    std::cout << "simulation finished\n";
}
