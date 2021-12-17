//
// Created by Meevere on 16.12.2021.
//

#ifndef ARX_PERLINNOISE_H
#define ARX_PERLINNOISE_H

//https://www.youtube.com/watch?v=6-0UaeJBumA

#include <vector>

std::vector<float> PerlinNoise1D( const std::vector<float>& seed, int nOctaves );
//std::vector<float> PerlinNoise2D( const std::vector<float>& seed, int nOctaves )

int testNoise();

#endif //ARX_PERLINNOISE_H
