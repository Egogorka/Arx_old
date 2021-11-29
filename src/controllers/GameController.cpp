//
// Created by Meevere on 29.11.2021.
//

#include "GameController.h"

#include <memory>
#include "src/model/structures/Environment.h"

GameController::GameController(std::shared_ptr<Drawer> drawer)
: drawer(drawer), container(1, 30, 30) {
    view = std::make_shared<View>(drawer);
}

void GameController::init() {


    int width = 20; int height = 20;

    // Generate 20 trees
    for (int i = 0; i < 20; ++i) {
        int x = std::rand() % 30;
        int y = std::rand() % 30;
        Vector3i pos{0,x,y};
        if(container.empty_at(pos))
            container.add_at(pos,
             std::make_shared<Environment>(Environment(Environment::Type::Tree, pos)));
    }

    // Generate 30 rocks
    for (int i = 0; i < 20; ++i) {
        int x = std::rand() % 30;
        int y = std::rand() % 30;
        Vector3i pos{0,x,y};
        if(container.empty_at(pos))
            container.add_at(pos,
             std::make_shared<Environment>(Environment::Type::Rock, pos));
    }

    drawer->add_event_listener(
        Drawer::Event::EventType::MousePressed,
        std::function{[=](const Drawer::Event& event) {
            int mouse_x = event.mouseClick.position[0] / width;
            int mouse_y = event.mouseClick.position[1] / height;
            Vector3i pos{0,mouse_x,mouse_y};

            // Harvesting of resources
            if (event.mouseClick.button == DrawerEvent::MouseClick::MouseButton::Left) {
                if (auto ptr = std::dynamic_pointer_cast<Environment>(container.get_at(pos).front())) {
                    switch (ptr->type) {
                        case Environment::Type::Rock:
                            this->stone_resource.amount += 1;
                            break;
                        case Environment::Type::Tree:
                            this->wood_resource.amount += 1;
                            break;
                        default:
                            break;
                    }
                    // Delete the environment at point;
                    container.get_at(pos).pop_front();
                }
            } else

            // Building Storehouses
            if (event.mouseClick.button == DrawerEvent::MouseClick::MouseButton::Right) {
                if(this->wood_resource.amount > 5)
                    container.add_at(pos, std::make_shared<Storehouse>(pos));
            }
        }}
    );
}

void GameController::update() {

    for (int i = 0; i < size_x; ++i) {
        for (int j = 0; j < size_y; ++j) {
            Vector3i pos{0,i,j};

            view->drawCell(container.get_cell_at(pos));
            for(auto& ptr : container.get_at(pos)){
                view->drawObject(ptr);
            }
        }
    }

}
