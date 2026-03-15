//
// Created by stefa on 3/13/2026.
//

#include "../include/world_generator.h"
#include <iostream>

void world_generator::set_seed(int seed) {
    this->seed = seed;
}

void world_generator::generate_chunk(int i_chunk, int j_chunk, int ground[], int decoratives[]){
    for (int i=0;i<32;i++) {
        for (int j=0;j<32;j++) {
            int generated_tile=abs((i_chunk+j_chunk)%2);
//            generated_tile=0;
            ground[i*32+j]=generated_tile;
            //decoratives[i*32+j]=(i_chunk+j_chunk)%2;
        }
    }
}