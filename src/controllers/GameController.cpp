//
// Created by Meevere on 29.11.2021.
//

#include "GameController.h"

#include <memory>

#include "utility/PerlinNoise.h"

GameController::GameController(std::shared_ptr<Drawer> drawer)
: drawer(drawer), container(size_z, size_x, size_y) {
    view = std::make_shared<GameView>(drawer, container);
}

void GameController::init() {

    std::vector<std::vector<float>> seed2D(256);
    for (auto& elem : seed2D){
        elem = std::vector<float>(256);
        for (auto& elem1 : elem){
            elem1 = (float)rand() / (float)RAND_MAX;
        }
    }
    auto noise = PerlinNoise2D(seed2D, 10, 1.3f);

    for(auto& unit : container){
        auto pos = unit.pos;
        if(unit.pos.z() == 0) {

            if( noise[pos.x()][pos.y()] < 0.4f + 0.05f * (float)rand() / (float)RAND_MAX ){
                unit.cell.wall_type = Cell::MaterialType::Stone;
                unit.cell.floor_type = Cell::MaterialType::Stone;

                container.get(pos + Vector3i{1,0,0}).cell.floor_type = Cell::MaterialType::Grass;
                continue;
            } else {
                unit.cell.floor_type = Cell::MaterialType::Grass;
            }

        } else {
            auto temp = 1.0f - float(pos.z()) / size_z;
            if(noise[pos.x()][pos.y()] < 0.4f * temp){
                unit.cell.wall_type = Cell::MaterialType::Stone;
                unit.cell.floor_type = Cell::MaterialType::Stone;

                if(unit.pos.z() < size_z - 1)
                    container.get(pos + Vector3i{1,0,0}).cell.floor_type = Cell::MaterialType::Grass;
            }
        }
    }

    for(auto& unit : container){
        if(unit.cell.wall_type != Cell::MaterialType::None) continue;
        if(unit.cell.floor_type == Cell::MaterialType::None) continue;

        auto pos = unit.pos;

        // Generate rocks
        if( (float)rand() / (float)RAND_MAX < 0.05f ){
            unit.objects.emplace_back(
                    make_shared<Environment>(Environment(Environment::Type::Rock, pos)));
            continue;
        }

        // Generate trees
        if( (float)rand() / (float)RAND_MAX < 0.1f ){
            unit.objects.emplace_back(
                    make_shared<Environment>(Environment(Environment::Type::Tree, pos)));
        }
    }

    for (int i = 0; i < 10; ++i) {
        container.objects.push_back(make_shared<Dwarf>(Vector3i{0, size_x / 2, size_y / 2}));
    }

    drawer->add_event_listener(
        Drawer::Event::EventType::MousePressed,
        function{[=](const Drawer::Event& event) {
            auto temp = this->view->fromWindow2Model(Vector2f{(float)event.mouseClick.position.x(), (float)event.mouseClick.position.y()});
            int mouse_x = temp.x();
            int mouse_y = temp.y();
            Vector2f pos_f{(float)event.mouseClick.position.x(), (float)event.mouseClick.position.y()};
            Vector3i pos{0,mouse_x,mouse_y};

            // Harvesting of resources
            if (event.mouseClick.button == DrawerEvent::MouseClick::MouseButton::Left) {
                for(auto& item : container.objects) {
                    if(item->getObjectType() == "dwarf"){
                        auto dwarf = dynamic_pointer_cast<Dwarf>(item);
                        if(!dwarf->hasTask()) {
                            dwarf->break_at(Vector3i{0, mouse_x, mouse_y}, container);
                            break;
                        }
                    }
                }
            } else

            // Building Storehouses
            if (event.mouseClick.button == DrawerEvent::MouseClick::MouseButton::Right) {
//                if(this->wood_resource.amount > 5)
//                    container.get(pos).objects.emplace_back(std::make_shared<Storehouse>(pos));
                for(auto& item : container.objects) {
                    if(item->getObjectType() == "dwarf"){
                        auto dwarf = dynamic_pointer_cast<Dwarf>(item);
                        dwarf->go_to(Vector3i{0,mouse_x,mouse_y}, container);
                    }
                }
            }
        }}
    );

    drawer->add_event_listener(
    Drawer::Event::EventType::MouseScroll,
    function{[this](const Drawer::Event& event){
            auto scale = this->view->getScale();
            this->view->setScale(scale + event.mouseScroll.delta/10);
        }}
    );

    drawer->add_event_listener(
            Drawer::Event::EventType::MousePressed,
            function{[this](const Drawer::Event& event){
                if(event.mouseClick.button == DrawerEvent::MouseClick::MouseButton::Middle){
                    auto temp = get_vector_i2f(event.mouseClick.position) - this->drawer->getSize()/2;
                    this->view->setOrigin(get_vector_i2f(event.mouseClick.position));
                    this->view->offset -= temp;
                }
            }}
    );

    drawer->add_event_listener(
            Drawer::Event::EventType::KeyPressed,
            function{[this](const Drawer::Event& event){
                // Period means down
                if(event.key.type == DrawerEvent::Key::KeyType::Period){
                    this->view->z_level -= 1;
                } else
                if(event.key.type == DrawerEvent::Key::KeyType::Comma){
                    this->view->z_level += 1;
                }
            }}
    );
}

void GameController::update() {
    vector<Vector3i> previous_positions(container.objects.size());

    for (int i = 0; i < container.objects.size(); ++i) {
        if (container.objects[i]->getObjectType() == "dwarf") {
            auto temp = static_pointer_cast<Dwarf>(container.objects[i]);
            previous_positions[i] = temp->position;
        }
    }

    for (int i = 0; i < container.objects.size(); ++i) {
        auto& item = container.objects[i];
        if(item->getObjectType() == "dwarf"){
            auto dwarf = static_pointer_cast<Dwarf>(item);
            item->update();

            // Check for boundaries
            if(dwarf->position.x() >= size_x ||
               dwarf->position.y() >= size_y ||
               dwarf->position.x() < 0 ||
               dwarf->position.y() < 0 )
            {
                dwarf->position = previous_positions[i];
                continue;
            }

            // Dwarf break
            if(!container.get(dwarf->position).objects.empty() && dwarf->hasTask()) {
                container.get(dwarf->position).objects.pop_front();
                dwarf->setTask(false);
            }

            // Dwarf cannot step on rock
            if(!container.get(dwarf->position).objects.empty()) {
                dwarf->position = previous_positions[i];
            }

            //Check for collision with other dwarves (optional)
            for (int j = 0; j < container.objects.size(); ++j) {
                // Not check collision with himself
                if( j == i ) continue;
                if(item->getObjectType() != "dwarf_temp") continue;

                auto dwarf_temp = static_pointer_cast<Dwarf>(container.objects[j]);
                if(dwarf_temp->position.x() == dwarf->position.x() && dwarf_temp->position.y() == dwarf->position.y()) {
                    dwarf->position = previous_positions[i];
                    break;
                }
            }
        }
    }


    view->render();
}
