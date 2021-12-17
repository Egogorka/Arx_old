#include <iostream>

#include "src/controllers/App.h"

#include "utility/PerlinNoise.h"

int main() {
//    App app{};
//
//    app.loop();

    vector<float> seed(256);
    for (auto& elem : seed){
        elem = std::rand();
    }

}
