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
    sf::Texture tex_cell;
    sf::Texture tex_dwarf;

    // Link to container of GameController
    const Container& container;

public:
    float scale = 1;
    int size = 20;

    explicit GameView(std::shared_ptr<Drawer> drawer, const Container& container);

    void render();
    void drawObject(std::shared_ptr<Object> object);
    void drawCell(const Cell& cell);

private:
    Vector2f getPoint(const Vector2f& vec);
    Vector2f getPoint(const Vector2i& vec);

    void drawEnvironment(std::shared_ptr<Environment> environment);
    void drawStorehouse(std::shared_ptr<Storehouse> storehouse);
    void drawDwarf(std::shared_ptr<Dwarf> dwarf);
};


#endif //ARX_GAMEVIEW_H
