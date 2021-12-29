//
// Created by Meevere on 29.11.2021.
//

#include "GameView.h"

GameView::GameView(std::shared_ptr<Drawer> drawer, const Container& container) : drawer(drawer), container(container) {
    tex_tree.loadFromFile("../assets/Tree2.png");
    tex_stone.loadFromFile("../assets/Stone.png");
    tex_store.loadFromFile("../assets/Store.png");
    sprite_sheet.loadFromFile("../assets/spritesheet1.png");
    tex_dwarf.loadFromFile("../assets/Dwarf.png");

    // Set initial offset (centring)
    auto centerWindow = Vector2f{(float)drawer->window.getSize().x, (float)drawer->window.getSize().y}/2;
    auto centerGame = fromModel2Window(container.getSize().getXY())/2;

    origin = centerGame;

    offset = centerWindow - centerGame;
}

//sf::Sprite GameView::manufactureSprite(const Object &object) {
//
//
//
//}

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
    sprite.setTexture(sprite_sheet);
    if(cell.wall_type == Cell::MaterialType::None){
        switch (cell.floor_type) {
            case Cell::MaterialType::Grass:
                sprite.setTextureRect(sf::IntRect{64, 240, 16, 16});
                sprite.setColor(sf::Color{100, 200, 30, 255});
                break;
            case Cell::MaterialType::Stone:
                sprite.setTextureRect(sf::IntRect{112, 32, 16, 16});
                break;
            case Cell::MaterialType::None:
            default:
                return;
        }
    } else
    if(cell.wall_type == Cell::MaterialType::Stone){
        sprite.setTextureRect(sf::IntRect{48, 128, 16, 16});
        sprite.setColor(sf::Color{80, 80, 100, 255});
    }


    auto temp = fromModel2Window(cell.position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale,scale);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}


void GameView::drawEnvironment(std::shared_ptr<Environment> environment) {
    sf::Sprite sprite;
    sprite.setTexture(sprite_sheet);
    if( environment->type == Environment::Type::Rock ) {
        sprite.setTextureRect(sf::IntRect{32,32,16,16});
        sprite.setColor(sf::Color::Cyan);
    } else
    if( environment->type == Environment::Type::Tree ) {
        sprite.setTextureRect(sf::IntRect{96,0,16,16});
        sprite.setColor(sf::Color::Green);
    }
    sprite.setScale(scale,scale);

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
//    sprite.setTexture(tex_dwarf);
//    sprite.setTextureRect(sf::IntRect{5,10,30-5,30-10});
    sprite.setTexture(sprite_sheet);
    sprite.setTextureRect(sf::IntRect{0,64,16,16});


    auto temp = fromModel2Window(dwarf->position.getXY());
    auto box = sprite.getLocalBounds();

//    sprite.setOrigin(box.width/2, box.height/2);
    sprite.setScale(scale*0.9,scale*0.9);
    sprite.setPosition(drawer->get_sf_vector(temp));

    drawer->window.draw(sprite);
}

void GameView::render() {
    for (int i = 0; i < container.getSize().x(); ++i) {
        for (int j = 0; j < container.getSize().y(); ++j) {
            if(z_level >= 0 and z_level < container.getSize().z() )
                drawCell(container.get(z_level, i, j).cell);
        }
    }

    for (int i = 0; i < container.getSize().x(); ++i) {
        for (int j = 0; j < container.getSize().y(); ++j) {
            if(z_level >= 0 and z_level < container.getSize().z() )
                for(auto& ptr : container.get(z_level, i, j).objects )
                    drawObject(ptr);
        }
    }

//    for(auto& unit : container)
//        drawCell(unit.cell);
//
//    for(auto& unit : container)
//        for(auto& ptr : unit.objects)
//            drawObject(ptr);

    for(auto& obj : container.objects) {
        if(obj->position.z() == z_level)
            drawObject(obj);
    }
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
    auto old_scale = scale;
    scale = _scale;

    offset += origin*(old_scale - scale);
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

void GameView::setOrigin(Vector2f _origin) {
    origin = (_origin - offset)/scale;
}


