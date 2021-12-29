//
// Created by Meevere on 21.11.2021.
//

#include "DrawerEvents.h"

DrawerEvent::MouseClick::MouseClick(MouseClick::MouseButton button, const Vector2i &position)
        : button(button),
          position(position) {}

DrawerEvent::MouseClick::MouseClick(sf::Mouse::Button button, const Vector2i &position)
        : position(position),
          button(MouseButton::Left) // Temporary
{
    MouseButton temp_button;
    switch (button) {
        case sf::Mouse::Button::Right:
            temp_button = MouseButton::Right;
            break;
        case sf::Mouse::Button::Middle:
            temp_button = MouseButton::Middle;
            break;
        default:
        case sf::Mouse::Button::Left:
            temp_button = MouseButton::Left;
            break;
    }
    this->button = temp_button;
}

DrawerEvent::MouseMove::MouseMove(const Vector2i &position)
    : position(position) {}

DrawerEvent::Exit::Exit() = default;

DrawerEvent::DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::Exit &exit) :
    type(type), exit(exit) {}

DrawerEvent::DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseMove &mouseMove) :
    type(type), mouseMove(mouseMove) {}

DrawerEvent::DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseClick &mouseClick) :
    type(type), mouseClick(mouseClick) {}

DrawerEvent::DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseScroll &mouseScroll) :
    type(type), mouseScroll(mouseScroll) {}

DrawerEvent::DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::Key &key) :
    type(type), key(key) {}

DrawerEvent::DrawerEvent(): type(EventType::Invalid) {}

DrawerEvent::DrawerEvent(const DrawerEvent &event): type(event.type){
    switch (type) {
        case EventType::MousePressed:
        case EventType::MouseReleased:
            mouseClick = event.mouseClick;
            break;
        case EventType::MouseMove:
            mouseMove = event.mouseMove;
            break;
        case EventType::MouseScroll:
            mouseScroll = event.mouseScroll;
            break;
        case EventType::Exit:
            exit = event.exit;
        case EventType::Invalid:
            break;
    }
}

DrawerEvent::MouseScroll::MouseScroll(float delta, const Vector2i &position): delta(delta), position(position){}

DrawerEvent::MouseScroll::MouseScroll(const DrawerEvent::MouseScroll &scroll): delta(scroll.delta), position(scroll.position) {}

DrawerEvent::MouseScroll::MouseScroll(const sf::Event::MouseWheelScrollEvent &scroll) : delta(scroll.delta), position(Vector2i{scroll.x, scroll.y}){}

DrawerEvent::Key::Key(DrawerEvent::Key::KeyType type) : type(type) {}

DrawerEvent::Key::Key(sf::Keyboard::Key key): type(KeyType::Invalid) {
    if(key - sf::Keyboard::A)
        type = static_cast<KeyType>(key - sf::Keyboard::A);
}

DrawerEvent::DrawerEvent(const sf::Event &event): type(EventType::Invalid) {
    switch (event.type) {
        case sf::Event::Closed:
            type = EventType::Exit;
            exit = Exit();
            break;
        case sf::Event::MouseButtonPressed:
            type = EventType::MousePressed;
            mouseClick = MouseClick(
                    event.mouseButton.button,
                    Vector2i{event.mouseButton.x, event.mouseButton.y}
                    );
            break;
        case sf::Event::MouseButtonReleased:
            type = EventType::MouseReleased;
            mouseClick = MouseClick(
                    event.mouseButton.button,
                    Vector2i{event.mouseButton.x, event.mouseButton.y}
            );
            break;
        case sf::Event::MouseMoved:
            type = EventType::MouseMove;
            mouseMove = MouseMove(
                    Vector2i{event.mouseButton.x, event.mouseButton.y}
            );
            break;
        case sf::Event::MouseWheelScrolled:
            type = EventType::MouseScroll;
            mouseScroll = MouseScroll(event.mouseWheelScroll);
            break;
        case sf::Event::KeyPressed:
            type = EventType::KeyPressed;
            key = Key(event.key.code);
            break;
        default:
            type = EventType::Invalid;
            break;
    }
}
