//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_APP_H
#define ARX_APP_H

//#include "interfaces/view/DrawerInterface.h"
#include "src/view/drawer/Drawer.h"
#include <memory>

#include "GameController.h"

#define RESOLUTION_X 800
#define RESOLUTION_Y 800

#define RESOLUTION Vector2f{RESOLUTION_X, RESOLUTION_Y}

class App {
    shared_ptr<Drawer> drawer;

    unique_ptr<GameController> gameController;

    bool flag;

    bool is_running;
public:
    App();

    void loop();

    void end();
};


#endif //ARX_APP_H
