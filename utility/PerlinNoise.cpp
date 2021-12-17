//
// Created by Meevere on 16.12.2021.
//

#include "PerlinNoise.h"

std::vector<float> PerlinNoise1D( const std::vector<float>& seed, int nOctaves ) {
    // For each element in array
    std::vector<float> output(seed.size());
    for (int x = 0; x < seed.size(); ++x) {
        float fNoise = 0.0f;
        float fScale = 1.0f;

        for (int j = 0; j < nOctaves; ++j) {
            int nPitch = seed.size() >> j;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % seed.size();

            float fBlend = (float)(x - nSample1)/(float)(nPitch);
            float fSample = (1.0f - fBlend) * seed[nSample1] + fBlend * seed[nSample2];
            fNoise +=  fSample * fScale;

            fScale /= 2.0f;
        }
        output[x] = fNoise;
    }
    return std::move(output);
}

std::vector<float> PerlinNoise2D( const std::vector<float>& seed, int nOctaves ) {
    // For each element in array
    std::vector<float> output(seed.size());
    for (int x = 0; x < seed.size(); ++x) {
        float fNoise = 0.0f;
        float fScale = 1.0f;

        for (int j = 0; j < nOctaves; ++j) {
            int nPitch = seed.size() >> j;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % seed.size();

            float fBlend = (float)(x - nSample1)/(float)(nPitch);
            float fSample = (1.0f - fBlend) * seed[nSample1] + fBlend * seed[nSample2];
            fNoise +=  fSample * fScale;

            fScale /= 2.0f;
        }
        output[x] = fNoise;
    }
    return std::move(output);
}

#include <SFML/Graphics.hpp>
#include <vector>

int testNoise() {
    std::vector<float> seed(256);
    for (auto& elem : seed){
        elem = (float)rand() / (float)RAND_MAX;
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(512, 512), "Test", sf::Style::Default);
    window.setFramerateLimit(60);

    int n = 5;

    while(true){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                goto EXIT;
            } else
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::A) {
                    n += 1;
                } else
                if(event.key.code == sf::Keyboard::B) {
                    n -= 1;
                } else
                if(event.key.code == sf::Keyboard::C) {
                    for (auto& elem : seed){
                        elem = (float)rand() / (float)RAND_MAX;
                    }
                }
            }
        }
        window.clear(sf::Color::White);

        auto noise = PerlinNoise1D(seed, n);
        for (int i = 0; i < noise.size(); ++i) {
            sf::RectangleShape rec;
//            std::cout << noise[i] << '\n';
            rec.setFillColor(sf::Color::Black);
            rec.setSize(sf::Vector2f(2, 256*noise[i]));
            rec.setPosition(sf::Vector2f(2*i,0));
            window.draw(rec);
        }
        window.display();
    }
    EXIT:
    return 0;
}