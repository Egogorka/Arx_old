//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_DRAWEREVENTS_H
#define ARX_DRAWEREVENTS_H

#include "utility/Vector.h"
#include <SFML/Window/Mouse.hpp>

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
        Exit,
        Invalid
    };
    EventType type;

    union {
        MouseClick mouseClick;
        MouseMove mouseMove;
        Exit exit;
    };

    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::Exit &exit);
    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseMove &mouseMove);
    DrawerEvent(DrawerEvent::EventType type, const DrawerEvent::MouseClick &mouseClick);
    DrawerEvent();
};





#endif //ARX_DRAWEREVENTS_H
