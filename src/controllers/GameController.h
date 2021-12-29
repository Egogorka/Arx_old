//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_GAMECONTROLLER_H
#define ARX_GAMECONTROLLER_H

#include <memory>
using namespace std;

#include "src/model/Container.h"

// view thingies

#include "src/view/drawer/Drawer.h"
#include "src/view/drawer/DrawerEvents.h"

#include "src/view/view_model/GameView.h"

class GameController {

    // Gets from parent controller
    shared_ptr<Drawer> drawer;
    shared_ptr<GameView> view;

    int size_z = 3;
    int size_x = 70;
    int size_y = 70;

    // Makes itself
    Container container;

    Resource stone_resource{Resource::Type::Stone};
    Resource wood_resource{Resource::Type::Wood};
//    Resource fish_resource;

public:
    explicit GameController(shared_ptr<Drawer> drawer);

    void init();

    void update();
};


#endif //ARX_GAMECONTROLLER_H
