//
// Created by Meevere on 29.11.2021.
//

#ifndef ARX_VIEW_H
#define ARX_VIEW_H

#include <memory>
#include "src/view/drawer/Drawer.h"
#include "src/model/Object.h"

#include "src/model/structures/all.h"
#include "src/model/Cell.h"

#include <SFML/Graphics.hpp>

class View {
    std::shared_ptr<Drawer> drawer;

    sf::Texture tex_tree;
    sf::Texture tex_stone;
    sf::Texture tex_store;
    sf::Texture tex_cell;

public:
    float scale = 1;
    int size = 40;

    explicit View(std::shared_ptr<Drawer> drawer);

    void drawObject(std::shared_ptr<Object> object);
    void drawCell(const Cell& cell);

private:
    Vector2f getPoint(const Vector2f& vec);
    Vector2f getPoint(const Vector2i& vec);

    void drawEnvironment(std::shared_ptr<Environment> environment);
    void drawStorehouse(std::shared_ptr<Storehouse> storehouse);
//    void drawDwarf(std::shared_ptr<Resource>&& resource);
};


#endif //ARX_VIEW_H
