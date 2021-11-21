//
// Created by Meevere on 21.11.2021.
//

#include "App.h"
#include "src/view/drawer/Drawer.h"

App::App():is_running(false) {
    drawer = std::make_unique<Drawer>(RESOLUTION);
}

void App::loop() {
//    is_running = true;
//    while(is_running){
//        drawer->clear();
//        drawer->display();
//    };
}

void App::end() {
    this->is_running = false;
}
