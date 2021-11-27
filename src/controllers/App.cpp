//
// Created by Meevere on 21.11.2021.
//

#include "App.h"
#include "src/view/drawer/Drawer.h"

#include "src/model/Dwarf.h"

App::App():is_running(false) {
    drawer = std::make_unique<Drawer>(RESOLUTION);
    flag = false;

//    static Vector2i last_point{};
//    static bool flag_2 = false;
//
//    drawer->add_event_listener(
//    Drawer::Event::EventType::MousePressed,
//    std::function{[this](const Drawer::Event& event){
//            if(event.mouseClick.button == Drawer::Event::MouseClick::MouseButton::Left)
//                this->flag = !this->flag;
//            else {
//                if(!flag_2) {
//                    last_point = event.mouseClick.position;
//                } else {
//                    this->lines.emplace_back(last_point, event.mouseClick.position);
//                }
//                flag_2 = !flag_2;
//            }
//        }}
//    );
//
//    drawer->add_event_listener(
//    Drawer::Event::EventType::MouseMove,
//    std::function{[this](const Drawer::Event& event) {
//            if(this->flag)
//                this->circles.emplace_back(std::make_pair(5, event.mouseMove.position));
//        }}
//    );

    drawer->add_event_listener(
        Drawer::Event::EventType::Exit,
        std::function{[this](const Drawer::Event& event){ this->is_running = false; }}
    );
}

void App::loop() {
    is_running = true;

    std::vector<Dwarf> dwarves{};
    dwarves.reserve(10);
    // Factory for that must be created
    for (int i = 0; i < 10; ++i) {
        auto temp = Vector3i{rand() % 20, rand() % 20, rand() % 20};
        dwarves.emplace_back(temp);
    }

    while(is_running){
        drawer->clear();
        drawer->handle_events();
/*        for(auto pair : this->circles){
            drawer->draw_circle(pair.first, pair.second);
        }
        for(auto pair : this->lines){
            drawer->draw_line(pair.first, pair.second, Color::Blue);
        }*/
        // Must be moved into model or something like that
        for(auto& dwarf : dwarves){
            dwarf.position += Vector3i{rand() % 3 - 1,rand() % 3 - 1,rand() % 3 - 1};
        }

        // Must be in view
        for(auto& dwarf : dwarves){
            drawer->draw_circle((float)dwarf.position[0],
                                10*Vector2i{dwarf.position[1], dwarf.position[2]},
                                Color::Green
                                );
        }

        drawer->display();
    };
}

void App::end() {
    this->is_running = false;
}
