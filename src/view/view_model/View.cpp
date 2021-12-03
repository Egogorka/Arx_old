//
// Created by Meevere on 29.11.2021.
//

#include "View.h"

View::View(std::shared_ptr<Drawer> drawer) : drawer(drawer) {
    tex_tree.loadFromFile("../assets/Tree2.png");
    tex_stone.loadFromFile("../assets/Stone.png");
    tex_store.loadFromFile("../assets/Store.png");
    tex_cell.loadFromFile("../assets/Grass.png");
}


void View::drawObject(std::shared_ptr<Object> object) {
    if(auto ptr1 = std::dynamic_pointer_cast<Environment>(object)){
        drawEnvironment(ptr1);
    } else
    if(auto ptr2 = std::dynamic_pointer_cast<Storehouse>(object)){
        drawStorehouse(ptr2);
    }
}

void View::drawCell(const Cell &cell) {
    auto temp = scale * size * Vector2i{cell.position[1], cell.position[2]};
    sf::Sprite sprite;
    sprite.setTexture(tex_cell);
    sprite.setPosition(drawer->get_sf_vector(temp));
    sprite.setScale(scale*0.9f,scale*0.9f);
    drawer->window.draw(sprite);
}

void View::drawEnvironment(std::shared_ptr<Environment> environment) {
    auto temp = scale * size * Vector2i{environment->position[1], environment->position[2]};
    sf::Sprite sprite;
    if( environment->type == Environment::Type::Rock ) {
        sprite.setTexture(tex_stone);
    } else
    if( environment->type == Environment::Type::Tree ) {
        sprite.setTexture(tex_tree);
    }
    sprite.setPosition(drawer->get_sf_vector(temp));
    sprite.setScale(scale*0.1,scale*0.1);

    drawer->window.draw(sprite);
}

void View::drawStorehouse(std::shared_ptr<Storehouse> storehouse) {
    auto temp = size * Vector2i{storehouse->position[1], storehouse->position[2]};
    sf::Sprite sprite;
    sprite.setTexture(tex_store);
    sprite.setPosition(drawer->get_sf_vector(temp));
    sprite.setScale(scale*0.9,scale*0.9);
    drawer->window.draw(sprite);
}
