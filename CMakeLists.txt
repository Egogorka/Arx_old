cmake_minimum_required(VERSION 3.17)
project(Arx)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(Arx
        main.cpp
        src/controllers/App.cpp src/controllers/App.h
        src/view/drawer/Drawer.cpp src/view/drawer/Drawer.h
        utility/Vector.h
        interfaces/view/DrawerInterface.h
        src/view/drawer/DrawerEvents.cpp
        src/view/drawer/DrawerEvents.h
        src/model/Cell.cpp src/model/Cell.h
        src/model/Dwarf.cpp src/model/Dwarf.h
        src/view/Color.cpp src/view/Color.h
        src/model/Container.cpp
        src/model/Container.h
        src/model/Object.cpp
        src/model/Object.h
        src/model/structures/Resource.cpp
        src/model/structures/Resource.h
        src/model/structures/Environment.cpp
        src/model/structures/Environment.h
        src/model/structures/Storehouse.cpp
        src/model/structures/Storehouse.h
        src/controllers/GameController.cpp
        src/controllers/GameController.h
        src/view/view_model/GameView.cpp
        src/view/view_model/GameView.h
        src/model/structures/all.h
#        src/controllers/MenuController.cpp
#        src/controllers/MenuController.h
#        utility/Eventer.h
        utility/PerlinNoise.cpp
        utility/PerlinNoise.h src/controllers/MenuController.cpp src/controllers/MenuController.h)

include_directories(utility, ../Arx)

if (WIN32)
    set(SFML_DIR ../SFML-2.5.1/lib/cmake/SFML)
    file(GLOB BINARY_DEP_DLLS "../SFML-2.5.1/bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Arx PRIVATE sfml-graphics sfml-audio nlohmann_json::nlohmann_json)