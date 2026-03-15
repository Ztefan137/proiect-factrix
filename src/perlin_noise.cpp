//
// Created by stefa on 3/14/2026.
//

#include "../include/perlin_noise.h"
#include <cmath>
#include <cstdint>

struct vector {
    float x;
    float y;
};
static uint32_t hash32(uint32_t x) {
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    x ^= x >> 16;
    return x;
}

vector hashDirection(int i, int j) {
    uint32_t h = hash32((uint32_t)i * 0x9e3779b9u ^ (uint32_t)j);
    float t = (h & 0xFFFFFF) / float(0xFFFFFF);
    float angle = t * 6.28318530718f;
    return { std::cos(angle), std::sin(angle) };
}
