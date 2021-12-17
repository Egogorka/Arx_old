//
// Created by Meevere on 29.11.2021.
//

#include "GameView.h"

GameView::GameView(std::shared_ptr<Drawer> drawer, const Container& container) : drawer(drawer), container(container) {
    tex_tree.loadFromFile("../assets/Tree2.png");
    tex_stone.loadFromFile("../assets/Stone.png");
    tex_store.loadFromFile("../assets/Store.png");
    tex_cell.loadFromFile("../assets/Grass.png");
    tex_dwarf.loadFromFile("../assets/Dwarf.png");

    // Set initial offset (centring)
    auto centerWindow = Vector2f{(float)drawer->window.getSize().x, (float)drawer->window.getSize().y}/2;
    auto centerGame = fromModel2Window(container.getSize().getXY())/2;

    offset = centerWindow - centerGame;
}


void GameView::drawObject(std::shared_ptr<Object> object) {
    if(object->getObjectType() == "environment"){
        auto ptr = std::static_pointer_cast<Environment>(object);
        drawEnvironment(ptr);
    } else
    if(object->getObjectType() == "storehouse"){
        auto ptr = std::static_pointer_cast<Storehouse>(object);
        drawStorehouse(ptr);
    }
    if(object->getObjectType() == "dwarf"){
        auto ptr = std::static_pointer_cast<Dwarf>(object);
        drawDwarf(ptr);
    }
}

void GameView::drawCell(const Cell &cell) {
    sf::Sprite sprite;
    sprite.setTexture(tex_cell);

    auto temp = fromModel2Window(cell.position.getXY());
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

    auto temp = fromModel2Window(environment->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);

    sprite.setPosition(drawer->get_sf_vector(temp));
    drawer->window.draw(sprite);
}


void GameView::drawStorehouse(std::shared_ptr<Storehouse> storehouse) {
    sf::Sprite sprite;
    sprite.setTexture(tex_store);

    auto temp = fromModel2Window(storehouse->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}

void GameView::drawDwarf(std::shared_ptr<Dwarf> dwarf) {
    sf::Sprite sprite;
    sprite.setTexture(tex_dwarf);
    sprite.setTextureRect(sf::IntRect{5,10,30-5,30-10});

    auto temp = fromModel2Window(dwarf->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}

void GameView::render() {
    for(auto& unit : container)
        drawCell(unit.cell);

    for(auto& unit : container)
        for(auto& ptr : unit.objects)
            drawObject(ptr);

    for(auto& obj : container.objects)
        drawObject(obj);
}

Vector2i GameView::fromWindow2Model(float x, float y) const {
    return fromWindow2Model(Vector2f{x,y});
}

Vector2f GameView::fromModel2Window(int x, int y) const {
    return fromModel2Window(Vector2i{x,y});
}

float GameView::getScale() const {
    return scale;
}

void GameView::setScale(float _scale) {
    auto old_size = getSize();
    scale = _scale;

    offset += (old_size - getSize())/2;
}

Vector2f GameView::getSize() {
    auto temp = container.getSize().getXY();
    return scale * size * Vector2f{(float)temp.x(), (float)temp.y()};
}

#include <cmath>

Vector2i GameView::fromWindow2Model(const Vector2f &pos) const {
    auto temp = (pos - offset)/scale/size;
    return Vector2i{(int)floor(temp.x()), (int)floor(temp.y())};
}

Vector2f GameView::fromModel2Window(const Vector2i &pos) const {
    return scale * size * Vector2f{(float)pos.x(),(float)pos.y()} + offset;
}

