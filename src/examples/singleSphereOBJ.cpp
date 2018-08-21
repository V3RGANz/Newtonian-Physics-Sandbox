#include "shell/npsworld.hpp"
#include "../import/npsimporter.hpp"

int main() {
    SimpleOBJSpheresImporter spheresImporter;
    spheresImporter.import("singleSphere.obj");

    NPSWorld npsWorld;

    int index = 0;
    auto cbody = spheresImporter.getObjects().front();
    std::cout << "Sphere" + std::to_string(index) << "\n";
    auto list = spheresImporter.getObjects();
    std::cout << "list.cellSize()" << list.size() << "\n";
    std::cout << list.front() << "\n";

    for (const auto &sphere : list) {
        std::cout << "copiyng : " << sphere << "\n";
        npsWorld.addBody("Sphere" + std::to_string(index++), sphere);
    }

    std::cout << "copying finished\n";

    npsWorld.start();

    return 0;
}
