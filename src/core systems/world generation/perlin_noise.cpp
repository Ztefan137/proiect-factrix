//
// Created by stefa on 3/14/2026.
//

#include "../../../include/perlin_noise.h"
#include <cmath>
#include <cstdint>
#include <iostream>

struct vector {
    float x;
    float y;
};
uint32_t hash2D(int x, int y, int seed=123) {
    uint32_t h = x * 374761393u + y * 668265263u + seed * 1442695041u;
    h ^= h >> 13;
    h *= 1274126177u;
    return h;
}

float hashToAngle(uint32_t h) {
    return (h / static_cast<float>(0xFFFFFFFFu)) * 6.28318530718f;
}

vector hashDirection(int i, int j,int seed=123) {
    uint32_t h = hash2D(i, j, seed);   // must match JS exactly
    float angle = hashToAngle(h);      // must match JS exactly
    return { std::cos(angle), std::sin(angle) };
}

inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
}
inline float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
inline float dot_product(vector a,vector b) {
    return a.x * b.x + a.y * b.y;
}
perlin_noise::perlin_noise(int seed){
    this->seed = seed;
}

void perlin_noise::set_seed(int new_seed) {
    this->seed = new_seed;
}

float perlin_noise::value(float x, float y) {
    int x0 = floor(x);
    int y0 = floor(y);

    vector g00=hashDirection(x0,y0,this->seed);
    vector g01=hashDirection(x0+1,y0,this->seed);
    vector g10=hashDirection(x0,y0+1,this->seed);
    vector g11=hashDirection(x0+1,y0+1,this->seed);

    float dx=x-x0;
    float dy=y-y0;

    vector d00={dx,dy};
    vector d01={dx-1,dy};
    vector d10={dx,dy-1};
    vector d11={dx-1,dy-1};

    float dp00=dot_product(g00,d00);
    float dp01=dot_product(g01,d01);
    float dp10=dot_product(g10,d10);
    float dp11=dot_product(g11,d11);

    float u=fade(dx);
    float v=fade(dy);

    float x1=lerp(dp00,dp01,u);
    float x2=lerp(dp10,dp11,u);

    return lerp(x1,x2,v);
}

float perlin_noise::value2(float x,float y,float amplitude,float frequency,int octaveCount,float persistence,float lacunarity){
    float value = 0.0f;
    for (int i = 0; i < octaveCount; i++) {
        value += amplitude * this->value(x * frequency, y * frequency);
        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return value;
}

