#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
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

    a.detectCollision(b);

    b.detectCollision(a);

    a.detectCollision(a);

    return 0;
}
