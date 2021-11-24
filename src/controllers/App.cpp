//
// Created by Meevere on 21.11.2021.
//

#include "App.h"
#include "src/view/drawer/Drawer.h"

App::App():is_running(false) {
    drawer = std::make_unique<Drawer>(RESOLUTION);
    drawer->add_event_listener(
    Drawer::Event::EventType::MousePressed,
    std::function{[this](const Drawer::Event& event) {
            std::cout << event.mouseClick.position;
            this->drawer->draw_circle(5, event.mouseClick.position);
        }}
    );
    drawer->add_event_listener(
        Drawer::Event::EventType::Exit,
        std::function{[this](const Drawer::Event& event){
            this->is_running = false;
        }}
    );
}

void App::loop() {
    is_running = true;
    while(is_running){
//        drawer->clear();
        drawer->handle_events();
        drawer->display();
    };
}

void App::end() {
    this->is_running = false;
}
