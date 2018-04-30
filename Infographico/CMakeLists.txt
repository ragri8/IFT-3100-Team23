cmake_minimum_required(VERSION 3.7)
set(OF_MAIN_DIR /home/deziar27/of_v0.9.8_linux64_release)
project(Infographico)
include(includelist.cmake)


#find_package(PkgConfig REQUIRED)
#pkg_search_module(CAIRO REQUIRED cairo)
#pkg_search_module(ZLIB REQUIRED zlib)
#pkg_search_module(GLEW REQUIRED glew)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES src/main.cpp src/application.h src/application.cpp src/renderer.cpp src/renderer.h
        src/primitives/primitive.cpp src/primitives/primitive.h src/primitives/line.cpp src/primitives/line.h
        src/primitives/rectangle.cpp src/primitives/rectangle.h src/primitives/circle.cpp src/primitives/circle.h
        src/model2D.cpp src/model2D.h src/primitives/triangleRect.cpp src/primitives/triangleRect.h src/historic.cpp
        src/historic.h src/primitives/triangle.cpp src/primitives/triangle.h src/raycast_classes/RayCastCamera.cpp
        src/raycast_classes/RayCastCamera.h src/raycast_classes/RayCastImage.cpp src/raycast_classes/RayCastImage.h
        src/raycast_classes/RayCastPlane.cpp src/raycast_classes/RayCastPlane.h src/raycast_classes/RayCastRay.h
        src/raycast_classes/RayCastSphere.cpp src/raycast_classes/RayCastSphere.h src/raycast_classes/SurfaceType.h
        src/raycast_classes/Vector.cpp src/raycast_classes/Vector.h)
add_executable(app ${SOURCE_FILES})
#configure_file(${FMODEX_DIR}/lib/osx/libfmodex.dylib ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#add_custom_target(XCode COMMAND make -C .. -j8)
add_custom_target(Makefile COMMAND cd .. && make)
