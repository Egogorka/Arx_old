cmake_minimum_required(VERSION 3.17)
project(Arx)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arx
        main.cpp
        src/controllers/App.cpp src/controllers/App.h
        src/view/drawer/Drawer.cpp src/view/drawer/Drawer.h
        utility/Vector.h
        interfaces/view/DrawerInterface.h src/view/drawer/DrawerEvents.cpp src/view/drawer/DrawerEvents.h src/model/Map.cpp src/model/Map.h src/model/Cell.cpp src/model/Cell.h src/model/Dwarf.cpp src/model/Dwarf.h src/view/drawer/Sprite.cpp src/view/drawer/Sprite.h src/view/Color.cpp src/view/Color.h src/view/view_model/DwarfView.cpp src/view/view_model/DwarfView.h)

include_directories(utility, ../Arx)

if (WIN32)
    set(SFML_DIR ../SFML-2.5.1/lib/cmake/SFML)
    file(GLOB BINARY_DEP_DLLS "../SFML-2.5.1/bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Arx sfml-graphics sfml-audio)