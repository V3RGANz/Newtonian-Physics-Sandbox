#define NEWTONIAN_PHYSICS_SANDBOX_DEBUG
#include "shell/npsworld.hpp"
#include "physics/body/composedSpheresCB.hpp"
#include "physics/collision/collisionResolve.hpp"

int main()
{
    NPSWorld npsWorld;

    ComposedSpheresCB balls[5] = {
        ComposedSpheresCB{{
                              {FloatCoord<3>(1, 0, 0), 0.5}
                          }},
        ComposedSpheresCB{{
                              {FloatCoord<3>(2, 0, 0), 0.5}
                          }},
        ComposedSpheresCB{{
                              {FloatCoord<3>(3, 0, 0), 0.5}
                          }},
        ComposedSpheresCB{{
                              {FloatCoord<3>(4, 0, 0), 0.5}
                          }},
        ComposedSpheresCB{{
                              {FloatCoord<3>(5, 0, 0), 0.5}
                          }}
    };

    ComposedSpheresCB whiteBall({
                                    {FloatCoord<3>(3, 0, 5), 0.5}
                                });

    POVRayTexture povRayTexture;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            povRayTexture.setPigment(10 * (i + 1) + j);
            balls[j].setTexture(povRayTexture);
            npsWorld.addToGroup("row" + std::to_string(i), balls[j]);
        }
        npsWorld.getGroup("row" + std::to_string(i))->movePosition(FloatCoord<3>(0.5 * i, 0, 0.5 * i));
    }

    povRayTexture.setPigment(POVRayColor::White);
    whiteBall.setTexture(povRayTexture);
    npsWorld.addBody("white", whiteBall);

    npsWorld.getBody("white")->setVelocity(FloatCoord<3>(0, 0, -0.05));

    std::cout << "SIMULATION STARTED\n";
    npsWorld.start();

    return 0;
}
