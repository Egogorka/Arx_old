//
// Created by Meevere on 21.11.2021.
//

#include "Drawer.h"

Drawer::Drawer(Vector2f resolution): resolution(resolution){
    window.create(sf::VideoMode(resolution[0], resolution[1]), "Test", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Drawer::draw_circle(float radius, const Vector2f &position) {
    sf::CircleShape shape(radius);
    shape.setPosition(position[0], position[1]);
    shape.setFillColor(sf::Color(100,250,50));
    window.draw(shape);
}

void Drawer::clear() {
    window.clear();
}

void Drawer::display() {
    window.display();
}

//void Drawer::handle_events() {
//    sf::Event event{};
//    auto view = get_instance();
//    while (view->window.pollEvent(event)){
//        if(event.type == sf::Event::Closed){
//            ExitEvent().invoke();
//        }
//        if(event.type == sf::Event::MouseButtonPressed){
//            if(event.mouseButton.button == sf::Mouse::Left){};
//            MouseClick(
//                    Vector2f{
//                            float(event.mouseButton.x),
//                            float(event.mouseButton.y)
//                    }).invoke();
//        }
//    }
//}
