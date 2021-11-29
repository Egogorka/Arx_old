//
// Created by Meevere on 26.11.2021.
//

#include "Color.h"

Color::Color(int r, int g, int b, int a) noexcept : r(r), g(g), b(b), a(a) {}

Color::Color(int r, int g, int b) noexcept : Color(r,g,b,0) {}

Color::Color(const sf::Color &color) noexcept : Color(color.r, color.g, color.b, color.a) {}

sf::Color Color::getSFMLColor() const {
    return sf::Color(r,g,b,255-a);
}

const Color Color::Red{255,0,0,0};
const Color Color::Green{0,255,0,0};
const Color Color::Blue{0,0,255,0};

const Color Color::White{255,255,255,0};
const Color Color::Grey{128,128,128,0};
const Color Color::Black{0,0,0,0};