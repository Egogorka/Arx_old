//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_DRAWERINTERFACE_H
#define ARX_DRAWERINTERFACE_H

#include "utility/Vector.h"
#include <queue>
// Better to move these events somewhere else
#include "src/view/drawer/DrawerEvents.h"
#include "src/view/Color.h"

namespace interfaces {

    class Drawer {
    public:

        /**
         * Draws a circle
         * @param radius
         * @param position (from the top left corner of the window)
         * @param color
         */
        virtual void draw_circle(float radius, const Vector2i &position, const Color& color) = 0;

        /**
         * Draws a line with specified color
         * @param a
         * @param b
         * @param color
         */
        virtual void draw_line(const Vector2i& a, const Vector2i& b, const Color& color) = 0;

        /**
         * Updates the window to show everything that was on screen
         */
        virtual void display() = 0;

        /**
         * Clears the window
         */
        virtual void clear() = 0;

        /**
         * Handles all of the events and returns a queue of them
         * (if you want to process them yourself instead of using handlers)
         */
        virtual std::queue<DrawerEvent> handle_events() = 0;
    };

}

#endif //ARX_DRAWERINTERFACE_H
