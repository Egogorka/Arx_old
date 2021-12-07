//
// Created by Meevere on 29.11.2021.
//

#include "GameView.h"

GameView::GameView(std::shared_ptr<Drawer> drawer, const Container& container) : drawer(drawer), container(container) {
    tex_tree.loadFromFile("../assets/Tree2.png");
    tex_stone.loadFromFile("../assets/Stone.png");
    tex_store.loadFromFile("../assets/Store.png");
    tex_cell.loadFromFile("../assets/Grass.png");
}


void GameView::drawObject(std::shared_ptr<Object> object) {
    if(auto ptr1 = std::dynamic_pointer_cast<Environment>(object)){
        drawEnvironment(ptr1);
    } else
    if(auto ptr2 = std::dynamic_pointer_cast<Storehouse>(object)){
        drawStorehouse(ptr2);
    }
}

void GameView::drawCell(const Cell &cell) {
    sf::Sprite sprite;
    sprite.setTexture(tex_cell);

    auto temp = getPoint(cell.position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}


void GameView::drawEnvironment(std::shared_ptr<Environment> environment) {
    sf::Sprite sprite;
    if( environment->type == Environment::Type::Rock ) {
        sprite.setTexture(tex_stone);
        sprite.setScale(scale*0.2,scale*0.2);
    } else
    if( environment->type == Environment::Type::Tree ) {
        sprite.setTexture(tex_tree);
        sprite.setScale(scale * 0.1, scale * 0.1);
    }

    auto temp = getPoint(environment->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);

    sprite.setPosition(drawer->get_sf_vector(temp));
    drawer->window.draw(sprite);
}


void GameView::drawStorehouse(std::shared_ptr<Storehouse> storehouse) {
    sf::Sprite sprite;
    sprite.setTexture(tex_store);

    auto temp = getPoint(storehouse->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}

void GameView::render() {

}

Vector2f GameView::getPoint(const Vector2f &vec) {
    return scale * size * vec;
}

Vector2f GameView::getPoint(const Vector2i &vec) {
    return getPoint(Vector2f{(float)vec.x(), (float)vec.y()});
}
