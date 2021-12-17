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

    sf::Vector2f get_sf_vector(const Vector2f& vec);
    sf::Vector2f get_sf_vector(const Vector2i& vec);
public:


    using Event = DrawerEvent;

    explicit Drawer(Vector2f resolution);

    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;

    void draw_circle(float radius, const Vector2i& position, const Color& color) override;
    void draw_circle(float radius, const Vector2i& position);

    void display() override;
    void clear() override;

    std::queue<DrawerEvent> handle_events() override;

    void draw_line(const Vector2i &a, const Vector2i &b, const Color &color) override;

    Vector2f getSize();

    friend class GameView;
};



#endif //ARX_DRAWER_H
