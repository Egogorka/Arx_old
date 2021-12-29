//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_GAMEVIEW_H
#define ARX_GAMEVIEW_H

#include <memory>
#include "src/view/drawer/Drawer.h"
#include "src/model/Object.h"

#include "src/model/structures/all.h"
#include "src/model/Dwarf.h"
#include "src/model/Cell.h"

#include "src/model/Container.h"

#include <SFML/Graphics.hpp>

class GameView {
    std::shared_ptr<Drawer> drawer;

    sf::Texture tex_tree;
    sf::Texture tex_stone;
    sf::Texture tex_store;
    sf::Texture tex_dwarf;
    sf::Texture sprite_sheet;

    // Link to container of GameController
    const Container& container;

    float scale = 1;

    // Center of scaling - does not scale itself
    Vector2f origin{0,0};

public:

    /**
     * Size of cells in pixels
     */
    int size = 16;

    /**
     * Currently displayed z-level
     */
    int z_level = 0;

    /**
     * Position of a left-upper corner of the field
     */
    Vector2f offset{0,0};

public:
    explicit GameView(std::shared_ptr<Drawer> drawer, const Container& container);

    void render();
    void drawObject(std::shared_ptr<Object> object);
    void drawCell(const Cell& cell);

    Vector2i fromWindow2Model( const Vector2f& pos ) const;
    Vector2f fromModel2Window( const Vector2i& pos ) const;

    Vector2i fromWindow2Model( float x, float y ) const;
    Vector2f fromModel2Window( int x, int y ) const;

    void setScale(float _scale);
    float getScale() const;
    Vector2f getSize();

    void setOrigin(Vector2f _origin);

private:
//    sf::Sprite manufactureSprite(const Object& object);

    void drawEnvironment(std::shared_ptr<Environment> environment);
    void drawStorehouse(std::shared_ptr<Storehouse> storehouse);
    void drawDwarf(std::shared_ptr<Dwarf> dwarf);
};


#endif //ARX_GAMEVIEW_H
