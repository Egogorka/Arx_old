//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_APP_H
#define ARX_APP_H

//#include "interfaces/view/DrawerInterface.h"
#include "src/view/drawer/Drawer.h"
#include <memory>

#define RESOLUTION_X 800
#define RESOLUTION_Y 800

#define RESOLUTION Vector2f{RESOLUTION_X, RESOLUTION_Y}

class App {
    std::unique_ptr<Drawer> drawer;

    std::vector<std::pair<float, Vector2i>> circles{};
    std::vector<std::pair<Vector2i, Vector2i>> lines{};

    bool flag;

    bool is_running;
public:
    App();

    void loop();

    void end();
};


#endif //ARX_APP_H
