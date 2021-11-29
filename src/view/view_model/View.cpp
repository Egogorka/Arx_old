//
// Created by Meevere on 29.11.2021.
//

#include "View.h"

View::View(std::shared_ptr<Drawer> drawer) : drawer(drawer) {}

void View::drawObject(std::shared_ptr<Object> object) {
    auto temp = object->getObjectType();
    if(auto ptr1 = std::dynamic_pointer_cast<Environment>(object)){
        drawEnvironment(ptr1);
    } else
    if(auto ptr2 = std::dynamic_pointer_cast<Storehouse>(object)){
        drawStorehouse(ptr2);
    }
}

void View::drawCell(const Cell &cell) {
    auto temp = Vector2i{20*cell.position[1], 20*cell.position[2]};
    drawer->draw_circle(10, temp);
}

void View::drawEnvironment(std::shared_ptr<Environment> environment) {
    auto temp = Vector2i{20*environment->position[1], 20*environment->position[2]};
    if( environment->type == Environment::Type::Rock )
        drawer->draw_circle(5, temp + Vector2i{5,5}, Color::Grey);
    else
    if( environment->type == Environment::Type::Tree )
        drawer->draw_circle(5, temp + Vector2i{5,5}, Color::Blue);
}

void View::drawStorehouse(std::shared_ptr<Storehouse> storehouse) {
    auto temp = Vector2i{20*storehouse->position[1], 20*storehouse->position[2]};
    drawer->draw_circle(15, temp - Vector2i{5,5}, Color::Red);
}
