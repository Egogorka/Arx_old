//
// Created by Meevere on 21.11.2021.
//

#include "Drawer.h"

Drawer::Drawer(Vector2f resolution): resolution(resolution){
    window.create(sf::VideoMode(resolution[0], resolution[1]), "Test", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Drawer::draw_circle(float radius, const Vector2i &position) {
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

std::queue<DrawerEvent> Drawer::handle_events() {
    std::queue<DrawerEvent> events;
    sf::Event event{};
    while (window.pollEvent(event)){
        Event temp;
        switch (event.type) {
            case sf::Event::Closed:
                temp = Event{DrawerEvent::EventType::Exit, Event::Exit{}};
                break;
            case sf::Event::MouseButtonPressed:
                temp = Event{Event::EventType::MousePressed, Event::MouseClick{
                        event.mouseButton.button,
                        Vector2i{event.mouseButton.x, event.mouseButton.y}
                }};
                break;
            case sf::Event::MouseButtonReleased:
                temp = Event{Event::EventType::MouseReleased, Event::MouseClick{
                        event.mouseButton.button,
                        Vector2i{event.mouseButton.x, event.mouseButton.y}
                }};
                break;
            default:
                break;
        }
        if( temp.type != Event::EventType::Invalid ) {
            evoke(temp);
            events.push(temp);
        }
    }
    return events;
}
