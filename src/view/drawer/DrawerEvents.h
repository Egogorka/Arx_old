//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_DRAWEREVENTS_H
#define ARX_DRAWEREVENTS_H

#include "utility/Vector.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

struct DrawerEvent {

    struct MouseClick {
        enum class MouseButton {
            Left, Right, Middle
        };
        MouseButton button;
        Vector2i position;

        MouseClick(MouseButton button, const Vector2i &position);
        // SFML Support
        MouseClick(sf::Mouse::Button button, const Vector2i &position);
    };

    struct MouseScroll {
        MouseScroll(const MouseScroll &scroll);

        Vector2i position;
        float delta;

        MouseScroll(float delta, const Vector2i &position);
        // SFML Support
        MouseScroll(const sf::Event::MouseWheelScrollEvent& scroll);
    };


    struct MouseMove {
        Vector2i position;
        explicit MouseMove(const Vector2i &position);
    };


    struct Exit {
        Exit();
    };

    enum class EventType {
        MouseMove,
        MousePressed,
        MouseReleased,
        MouseScroll,
        Exit,
        Invalid
    };
    EventType type;

    union {
        MouseClick mouseClick;
        MouseMove mouseMove;
        MouseScroll mouseScroll;
        Exit exit;
    };

    DrawerEvent();
    DrawerEvent(const DrawerEvent& event);

    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::Exit &exit);
    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseMove &mouseMove);
    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseClick &mouseClick);
    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseScroll &mouseScroll);
};





#endif //ARX_DRAWEREVENTS_H
