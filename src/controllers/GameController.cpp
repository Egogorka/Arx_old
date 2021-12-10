//
// Created by Meevere on 29.11.2021.
//

#include "GameController.h"

#include <memory>

GameController::GameController(std::shared_ptr<Drawer> drawer)
: drawer(drawer), container(1, 30, 30) {
    view = std::make_shared<GameView>(drawer, container);
}

void GameController::init() {
    float width  = view->scale * view->size;
    float height = width;

    // Generate 20 trees
    for (int i = 0; i < 20; ++i) {
        int x = std::rand() % size_x;
        int y = std::rand() % size_y;
        Vector3i pos{0,x,y};
        if(container.empty_at(pos))
            container.add_at(pos,
      make_shared<Environment>(Environment(Environment::Type::Tree, pos)));
    }

    // Generate 30 rocks
    for (int i = 0; i < 20; ++i) {
        int x = std::rand() % size_x;
        int y = std::rand() % size_y;
        Vector3i pos{0,x,y};
        if(container.empty_at(pos))
            container.add_at(pos,
            make_shared<Environment>(Environment::Type::Rock, pos));
    }

    for (int i = 0; i < 10; ++i) {
        container.objects.push_back(make_shared<Dwarf>(Vector3i{size_z / 2, size_x / 2, size_y / 2}));
    }

    drawer->add_event_listener(
        Drawer::Event::EventType::MousePressed,
        function{[=](const Drawer::Event& event) {
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
    for(auto& item : container.objects){
        item->update();
        if(item->getObjectType() == "dwarf"){
            auto temp = static_pointer_cast<Dwarf>(item);
            if(temp->position.x() >= size_x)
                temp->position.x() = size_x - 1;
            if(temp->position.y() >= size_y)
                temp->position.y() = size_y - 1;

            if(temp->position.x() < 0)
                temp->position.x() = 0;
            if(temp->position.y() < 0)
                temp->position.y() = 0;
        }
    }


    view->render();
}
