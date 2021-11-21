cmake_minimum_required(VERSION 3.17)
project(Arx)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arx
        main.cpp
        src/controllers/App.cpp src/controllers/App.h
        src/view/drawer/Drawer.cpp src/view/drawer/Drawer.h
        utility/Vector.h
        interfaces/view/DrawerInterface.h)

include_directories(utility, ../Arx)

if (WIN32)
    set(SFML_DIR ../SFML-2.5.1/lib/cmake/SFML)
    file(GLOB BINARY_DEP_DLLS "../SFML-2.5.1/bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Arx sfml-graphics sfml-audio)