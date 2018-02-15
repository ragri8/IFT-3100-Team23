cmake_minimum_required(VERSION 3.7)
set(OF_MAIN_DIR /home/deziar27/of_v0.9.8_linux64_release)
project(Infographico)
include(includelist.cmake)


#find_package(PkgConfig REQUIRED)
#pkg_search_module(CAIRO REQUIRED cairo)
#pkg_search_module(ZLIB REQUIRED zlib)
#pkg_search_module(GLEW REQUIRED glew)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES src/main.cpp src/ofApp.h src/ofApp.cpp)
add_executable(app ${SOURCE_FILES})
#configure_file(${FMODEX_DIR}/lib/osx/libfmodex.dylib ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#add_custom_target(XCode COMMAND make -C .. -j8)
add_custom_target(Makefile COMMAND cd .. && make)
