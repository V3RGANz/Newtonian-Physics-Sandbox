#include "phys.hpp"


{
    SerialSimulator<Container> sim(
        new GasInitializer(
            Coord<3>(10, 10, 10),
            80000));
    sim.addWriter(
        new GasWriter(
            "sim",
            200));

    sim.run();

    return 0;
}
