//
// Created by Meevere on 21.11.2021.
//

#ifndef ARX_DRAWERINTERFACE_H
#define ARX_DRAWERINTERFACE_H

#include "utility/Vector.h"

namespace interfaces {

    class Drawer {
    public:

        /**
         * Draws a circle
         * @param radius
         * @param position
         */
        virtual void draw_circle(float radius, const Vector2f &position) = 0;

        /**
         * Updates the window to show everything that was on screen
         */
        virtual void display() = 0;

        /**
         * Clears the window
         */
        virtual void clear() = 0;

    };

}

#endif //ARX_DRAWERINTERFACE_H
