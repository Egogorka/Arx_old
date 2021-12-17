#include <iostream>

#include "src/controllers/App.h"

#include "utility/PerlinNoise.h"

#include <SFML/Graphics.hpp>

int main() {
    App app{};

    app.loop();
}
