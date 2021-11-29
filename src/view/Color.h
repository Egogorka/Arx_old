//
// Created by Meevere on 26.11.2021.
//

#ifndef ARX_COLOR_H
#define ARX_COLOR_H

#include <SFML/Graphics/Color.hpp>

struct Color {
    int r;
    int g;
    int b;
    int a;

    Color(int r, int g, int b, int a) noexcept;
    Color(int r, int g, int b) noexcept;
    //SFML Support
    explicit Color(const sf::Color& color) noexcept;
    [[nodiscard]] sf::Color getSFMLColor() const;

    static const Color Red;
    static const Color Green;
    static const Color Blue;

    static const Color White;
    static const Color Grey;
    static const Color Black;
};

#endif //ARX_COLOR_H
