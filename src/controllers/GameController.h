//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_GAMECONTROLLER_H
#define ARX_GAMECONTROLLER_H

#include <memory>

#include "src/model/Container.h"

// view thingies

#include "src/view/drawer/Drawer.h"
#include "src/view/drawer/DrawerEvents.h"

#include "src/view/view_model/View.h"

class GameController {

    // Gets from parent controller
    std::shared_ptr<Drawer> drawer;
    std::shared_ptr<View> view;

    // Makes itself
    Container container;
    const int size_x = 30;
    const int size_y = 30;

    Resource stone_resource{Resource::Type::Stone};
    Resource wood_resource{Resource::Type::Wood};
//    Resource fish_resource;

public:
    explicit GameController(std::shared_ptr<Drawer> drawer);

    void init();

    void update();
};


#endif //ARX_GAMECONTROLLER_H
