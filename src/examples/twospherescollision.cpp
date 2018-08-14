#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include "shell/npsworld.hpp"
#include "physics/body/composedSpheresCB.hpp"
#include "physics/collision/collisionResolve.hpp"

int main()
{
    ComposedSpheresCB a ({
                             {FloatCoord<3>{1,1,1}, 1}
    });

    ComposedSpheresCB b ({
                             {FloatCoord<3>{4,4,4}, 2}
    });

//    a.setVelocity(FloatCoord<3>{-0.01,-0.01,-0.01});

    NPSWorld npsWorld;

    npsWorld.addBody("first", a);
    npsWorld.addBody("second", b);
    npsWorld.getBody("second")->setVelocity(FloatCoord<3>(-0.01,-0.01,-0.01));
    std::cout << "twospherescollision\n";
    npsWorld.start();

    return 0;
}
