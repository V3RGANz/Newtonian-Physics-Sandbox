cmake_minimum_required(VERSION 3.10)
project(Newtonian_Physics_Sandbox)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(src)

add_executable(Newtonian_Physics_Sandbox
        include/ntphyssbox.hpp
        src/examples/lonelySphere.cpp
        src/boundingObject.hpp
        src/boundingObjectTree.hpp
        src/boundingSphere.hpp
        src/cell.hpp
        src/collision.hpp
        src/collisionBody.hpp
        src/composedSpheresCB.hpp
        src/collisionDetection.hpp
        src/collisionTreeDetection.hpp
        )
