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
    sf::Sprite sprite;
    sprite.setTexture(tex_cell);

    auto temp = getPoint(cell.position.getXY());
    auto box = sprite.getLocalBounds();

    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}


void View::drawEnvironment(std::shared_ptr<Environment> environment) {
    sf::Sprite sprite;
    if( environment->type == Environment::Type::Rock ) {
        sprite.setTexture(tex_stone);
    } else
    if( environment->type == Environment::Type::Tree ) {
        sprite.setTexture(tex_tree);
    }

    auto temp = getPoint(environment->position.getXY());
    auto box = sprite.getLocalBounds();

    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.1,scale*0.1);

    sprite.setPosition(drawer->get_sf_vector(temp));
    drawer->window.draw(sprite);
}


void View::drawStorehouse(std::shared_ptr<Storehouse> storehouse) {
    sf::Sprite sprite;
    sprite.setTexture(tex_store);

    auto temp = getPoint(storehouse->position.getXY());
    auto box = sprite.getLocalBounds();

    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}

Vector2f View::getPoint(const Vector2f &vec) {
    return scale * size * vec;
}

Vector2f View::getPoint(const Vector2i &vec) {
    return getPoint(Vector2f{(float)vec.x(), (float)vec.y()});
}
