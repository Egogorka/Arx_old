//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_DRAWER_H
#define ARX_DRAWER_H

#include "interfaces/view/DrawerInterface.h"
#include "utility/Vector.h"

#include <SFML/Graphics.hpp>

#include "DrawerEvents.h"
#include "utility/Eventable.h"

class Drawer : public interfaces::Drawer, public Eventable<DrawerEvent>  {
private:
    Vector2f resolution;
    sf::RenderWindow window;
public:
    using Event = DrawerEvent;

    explicit Drawer(Vector2f resolution);

    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;

    void draw_circle(float radius, const Vector2i& position) override;
//    static void draw_sprite(const Sprite& sprite, const Vector2f& position);
    void display() override;
    void clear() override;

    std::queue<DrawerEvent> handle_events() override;
};


#endif //ARX_DRAWER_H
