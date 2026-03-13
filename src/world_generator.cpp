//
// Created by stefa on 3/13/2026.
//

#include "world_generator.h"

void world_generator::set_seed(int seed) {
    this->seed = seed;
}

void world_generator::generate_chunk(int i, int j, int ground[], int decoratives[]) {
    for (int i=0;i<32;i++) {
        for (int j=0;j<32;j++) {
            ground[i*32+j]=0;
            decoratives[i*32+j]=0;
        }
    }
}