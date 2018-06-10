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


//    NPSWorld npsWorld;

//    npsWorld.addBody(a);
//    npsWorld.addBody(b);

//    npsWorld.start();

    return 0;
}
