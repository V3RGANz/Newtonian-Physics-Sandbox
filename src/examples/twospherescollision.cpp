#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include "../npsworld.hpp"
#include "../composedSpheresCB.hpp"
#include "../collisionResolve.hpp"

int main()
{
    ComposedSpheresCB a ({
                             {FloatCoord<3>{0,0,0}, 1}
    });

    ComposedSpheresCB b ({
                             {FloatCoord<3>{0,1,0.7}, 2}
    });

    a.addVelocity(FloatCoord<3>{-0.001,-0.001,-0.001});
    a.applyVelocity();

    NPSWorld npsWorld;

    npsWorld.addBody("first", a);

//    npsWorld.addBody("second", b);

    npsWorld.start();

    return 0;
}
