//
// Created by stefa on 3/13/2026.
//

#include "../include/world_generator.h"
#include <../include/perlin_noise.h>
#include <iostream>

void world_generator::set_seed(int new_seed) {
    this->seed = new_seed;
}

void world_generator::generate_chunk(int i_chunk, int j_chunk, int ground[], int decoratives[]){
    perlin_noise elevation_noise(this->seed);
    perlin_noise temperature_noise(this->seed ^ 0xC1FE29D4);
    perlin_noise aridity_noise(this->seed ^ 0x9E3779B9);
    perlin_noise warp_noise(this->seed ^ 0x9E3779B9);
    for (int i=0;i<32;i++) {
        for (int j=0;j<32;j++) {
            float elevation=elevation_noise.value2(((float)(i_chunk*32+i))/100,((float)(j_chunk*32+j))/100,2,0.5,7,0.5,2);
            float warp_x=warp_noise.value2(((float)(i_chunk*32+i))*0.05,((float)(j_chunk*32+j))*0.05,2,0.02,2,0.5,2);
            float warp_y=warp_noise.value2(((float)(i_chunk*32+i))*0.05+1000,((float)(j_chunk*32+j))*0.05+1000,2,0.02,2,0.5,2);
            float temperature=temperature_noise.value2(((float)(i_chunk*32+i))/1000+warp_x,((float)(j_chunk*32+j))/1000+warp_y,1,0.5,7,0.5,2);
            float aridity=aridity_noise.value2(((float)(i_chunk*32+i))/1000-warp_x,((float)(j_chunk*32+j))/1000+warp_y,1,0.5,7,0.5,2);
            bool biome_1=temperature>0 && aridity<0;
            bool biome_2=temperature<0 && aridity<0;
            bool biome_3=(temperature>-1 && temperature<-0.3) && (aridity>0);
            bool biome_4=(temperature>-0.3 && temperature<0.3) && (aridity>0);
            bool biome_5=(temperature>0.3 && temperature<1) && (aridity>0);
            ground[i*32+j]=(elevation>-0.5)*(1*biome_1+2*biome_2+3*biome_3+4*biome_4+5*biome_5);
            decoratives[i*32+j]=0;
        }
    }

}