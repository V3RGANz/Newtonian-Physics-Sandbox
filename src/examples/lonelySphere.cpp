#include "../../include/ntphyssbox.hpp"

int main()
{

    ComposedSpheresCB a = ComposedSpheresCB({
        {FloatCoord<3>(0,0,0), 1}
    });

    NPSWorld npsWorld;

    npsWorld.addBody("sphere", a);

    npsWorld.start();

    return 0;
}