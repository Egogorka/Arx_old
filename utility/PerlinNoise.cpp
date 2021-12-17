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
