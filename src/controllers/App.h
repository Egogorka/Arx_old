//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_APP_H
#define ARX_APP_H

#include "interfaces/view/DrawerInterface.h"
#include <memory>

#define RESOLUTION_X 500
#define RESOLUTION_Y 500

#define RESOLUTION Vector2f{RESOLUTION_X, RESOLUTION_Y}

class App {
    std::unique_ptr<interfaces::Drawer> drawer;

    bool is_running;
public:
    App();

    void loop();

    void end();
};


#endif //ARX_APP_H
