cmake_minimum_required(VERSION 3.10)
project(Newtonian_Physics_Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)
include_directories(/usr/include/x86_64-linux-gnu/qt5/)
set (CMAKE_CXX_FLAGS -fPIC)
set (CMAKE_CXX_FLAGS -DQT_NO_VERSION_TAGGING)
link_directories(/usr/lib/x86_64-linux-gnu/qt5/)

add_executable(Newtonian_Physics_Sandbox
        include/ntphyssbox.hpp
        src/examples/lonelySphere.cpp
        src/physics/bounding/boundingObject.hpp
        src/physics/bounding/boundingObjectTree.hpp
        src/physics/bounding/boundingSphere.hpp
        src/cell.hpp
        src/physics/collision/collision.hpp
        src/physics/body/collisionBody.hpp
        src/physics/body/composedSpheresCB.hpp
        src/physics/collision/collisionDetection.hpp
        src/physics/collision/collisionTreeDetection.hpp
        src/physics/collision/collisionResolve.hpp
        src/math/tensor.hpp
        src/shell/writer.hpp
        src/shell/initializer.hpp
        src/physics/body/composedSpheresCB.cpp
        src/physics/collision/collisionResolve.cpp
        src/physics/body/collisionBody.cpp
        src/shell/npsworld.cpp
        src/shell/npsworld.hpp
        src/physics/bounding/axisalignedboundingbox.cpp
        src/physics/bounding/axisalignedboundingbox.hpp
        src/examples/twospherescollision.cpp
        src/examples/billiardBalls.cpp
        src/examples/NewtonsBalls.cpp
        src/import/npsimporter.cpp
        src/import/npsimporter.hpp
        src/examples/singleSphereOBJ.cpp
        src/physics/bounding/boundingSphere.cpp
        src/physics/collision/collision.cpp
        src/shell/initializer.cpp
        src/shell/writer.cpp src/shell/povraytexture.cpp src/shell/povraytexture.hpp src/math/tensor.cpp src/examples/composedSpheres.cpp)
