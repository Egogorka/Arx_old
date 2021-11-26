//
// Created by Meevere on 21.11.2021.
//

#include "App.h"
#include "src/view/drawer/Drawer.h"

App::App():is_running(false) {
    drawer = std::make_unique<Drawer>(RESOLUTION);
    flag = false;

    static Vector2i last_point{};
    static bool flag_2 = false;

    drawer->add_event_listener(
    Drawer::Event::EventType::MousePressed,
    std::function{[this](const Drawer::Event& event){
            if(event.mouseClick.button == Drawer::Event::MouseClick::MouseButton::Left)
                this->flag = !this->flag;
            else {
                if(!flag_2) {
                    last_point = event.mouseClick.position;
                } else {
                    std::cout << "Hmpf";
                    this->lines.emplace_back(last_point, event.mouseClick.position);
                }
                flag_2 = !flag_2;
            }
        }}
    );

    drawer->add_event_listener(
    Drawer::Event::EventType::MouseMove,
    std::function{[this](const Drawer::Event& event) {
            if(this->flag)
                this->circles.emplace_back(std::make_pair(5, event.mouseMove.position));
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
        drawer->clear();
        drawer->handle_events();
        for(auto pair : this->circles){
            drawer->draw_circle(pair.first, pair.second);
        }
        for(auto pair : this->lines){
            drawer->draw_line(pair.first, pair.second, Color::Blue);
        }
        drawer->display();
    };
}

void App::end() {
    this->is_running = false;
}
