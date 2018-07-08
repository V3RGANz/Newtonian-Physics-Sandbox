#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include "shell/npsworld.hpp"
#include "physics/body/composedSpheresCB.hpp"
#include "physics/collision/collisionResolve.hpp"

int main()
{
    ComposedSpheresCB a ({
                             {FloatCoord<3>{0,0,0}, 1}
    });

    ComposedSpheresCB b ({
                             {FloatCoord<3>{0,1,0.7}, 2}
    });

//    a.addVelocity(FloatCoord<3>{-0.001,-0.001,-0.001});

    NPSWorld npsWorld;

    npsWorld.addBody("first", a);

//    npsWorld.addBody("second", b);
    std::cout << "twospherescollision\n";
    npsWorld.start();

    return 0;
}
