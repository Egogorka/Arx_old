//
// Created by Meevere on 16.12.2021.
//

#include "PerlinNoise.h"

std::vector<float> PerlinNoise1D( const std::vector<float>& seed, int nOctaves, float scale ) {
    // For each element in array
    std::vector<float> output(seed.size());
    for (int x = 0; x < seed.size(); ++x) {
        float fNoise = 0.0f;
        float fScale = 1.0f;
        float fScaleAcc = 0.0f;

        for (int j = 0; j < nOctaves; ++j) {
            int nPitch = seed.size() >> j;
            if(nPitch == 0) continue;

            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % seed.size();

            float fBlend = (float)(x - nSample1)/(float)(nPitch);
            float fSample = (1.0f - fBlend) * seed[nSample1] + fBlend * seed[nSample2];
            fNoise +=  fSample * fScale;

            fScaleAcc += fScale;
            fScale /= scale;
        }
        output[x] = fNoise / fScaleAcc;
    }
    return std::move(output);
}

std::vector<std::vector<float>> PerlinNoise2D( const std::vector<std::vector<float>>& seed, int nOctaves, float scale  ) {
    std::vector<std::vector<float>> output(seed.size());
    for(auto& item : output){
        item = std::vector<float>(seed[0].size());
    }

    // For each element in array
    for (int x = 0; x < seed.size(); ++x) {
        for (int y = 0; y < seed[0].size(); ++y) {

            float fNoise = 0.0f;
            float fScale = 1.0f;
            float fScaleAcc = 0.0f;

            for (int j = 0; j < nOctaves; ++j) {
                int nPitch = seed.size() >> j;
                if(nPitch == 0) continue;

                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;

                int nSampleX2 = (nSampleX1 + nPitch) % seed.size();
                int nSampleY2 = (nSampleY1 + nPitch) % seed.size();

                float fBlendX = (float)(x - nSampleX1)/(float)(nPitch);
                float fBlendY = (float)(y - nSampleY1)/(float)(nPitch);

                float fSampleT = (1.0f - fBlendX) * seed[nSampleX1][nSampleY1] + fBlendX * seed[nSampleX2][nSampleY1];
                float fSampleB = (1.0f - fBlendX) * seed[nSampleX1][nSampleY2] + fBlendX * seed[nSampleX2][nSampleY2];
                fNoise +=  (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;

                fScaleAcc += fScale;
                fScale /= scale;
            }
            output[x][y] = fNoise / fScaleAcc;
        }
    }
    return std::move(output);
}

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int testNoise() {
    std::vector<float> seed(256);
    for (auto& elem : seed){
        elem = (float)rand() / (float)RAND_MAX;
    }

    std::vector<std::vector<float>> seed2D(256);
    for (auto& elem : seed2D){
        elem = std::vector<float>(256);
        for (auto& elem1 : elem){
            elem1 = (float)rand() / (float)RAND_MAX;
        }
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(512, 512), "Test", sf::Style::Default);
    window.setFramerateLimit(60);

    int n = 5;
    float scale = 2.0f;
    int mode = 1;

    while(true){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                goto EXIT;
            } else
            if(event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    // Change octaves
                    case sf::Keyboard::A:
                        n += 1;
                        break;
                    case sf::Keyboard::D:
                        n -= 1;
                        break;

                    // Change scalings
                    case sf::Keyboard::Q:
                        scale += 0.2f;
                        break;
                    case sf::Keyboard::E:
                        scale -= 0.2f;
                         break;

                    case sf::Keyboard::M:
                        if(mode == 1) {
                            mode = 2;
                        } else {
                            mode = 1;
                        }
                        break;
                    // Change seed
                    case sf::Keyboard::C:
                        if(mode == 1) {
                            for (auto &elem : seed) {
                                elem = (float) rand() / (float) RAND_MAX;
                            }
                        } else {
                            for (auto& elem : seed2D){
                                elem = std::vector<float>(256);
                                for (auto& elem1 : elem){
                                    elem1 = (float)rand() / (float)RAND_MAX;
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        window.clear(sf::Color::White);

        if(n == 10) n = 9;
        if(scale <= 0.2f) scale = 0.2f;

        if( mode == 1) {
            auto noise = PerlinNoise1D(seed, n, scale);
            for (int i = 0; i < noise.size(); ++i) {
                sf::RectangleShape rec;
//            std::cout << noise[i] << '\n';
                rec.setFillColor(sf::Color::Black);
                rec.setSize(sf::Vector2f(2, 256 * noise[i]));
                rec.setPosition(sf::Vector2f(2 * i, 0));
                window.draw(rec);
            }
        } else {
            auto noise = PerlinNoise2D(seed2D, n, scale);
            for (int i = 0; i < noise.size(); ++i) {
                for (int j = 0; j < noise[0].size(); ++j) {
                    sf::RectangleShape rec;
                    std::cout << noise[i][j] << '\n';
                    unsigned char temp = (unsigned char)(512 * noise[i][j]) % 255;
                    rec.setFillColor(sf::Color{temp, temp, temp});
                    rec.setSize(sf::Vector2f(2, 2));
                    rec.setPosition(sf::Vector2f(2 * i, 2 * j));
                    window.draw(rec);
                }
            }
        }
        window.display();
    }
    EXIT:
    return 0;
}