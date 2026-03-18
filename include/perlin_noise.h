//
// Created by stefa on 3/14/2026.
//

#ifndef OOP_PERLIN_NOISE_H
#define OOP_PERLIN_NOISE_H


class perlin_noise {
    int seed=0;
public:
    perlin_noise(int seed);
    void set_seed(int seed);
    float value(float x,float y);
    float value2(float x,float y,float amplitude,float frequency,int octaveCount,float persistence,float lacunarity);
};


#endif //OOP_PERLIN_NOISE_H