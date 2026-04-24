//
// Created by stefa on 3/13/2026.
//

#include "../../../include/world_generator.h"
#include <../include/perlin_noise.h>
#include <cmath>

/*inline float seededRand(int x, int y, int seed) { return static_cast<float>(((x* 73856093) ^ (y * 19349663) ^ seed) % 100) / 100.f; }*/
inline float seededRand(int x, int y, int seed) {
    unsigned int h = static_cast<unsigned int>(x) * 0x45d9f3b +
                     static_cast<unsigned int>(y) * 0x1234567 +
                     static_cast<unsigned int>(seed);
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = (h >> 16) ^ h;

    // Returns 0.0f to 1.0f
    return static_cast<float>(h) / static_cast<float>(0xFFFFFFFF);
}
void world_generator::set_seed(int new_seed) {
    this->seed = new_seed;
}

void world_generator::generate_chunk(int i_chunk, int j_chunk, int ground[], int decoratives[]) const{
    perlin_noise elevation_noise(this->seed);
    perlin_noise temperature_noise(this->seed ^ 0xC1FE29D4);
    perlin_noise aridity_noise(this->seed ^ 0x9E3779B9);
    perlin_noise ore_noise(this->seed ^ 0x122E29C9);
    perlin_noise ore_noise2(this->seed ^ 0xFF7529);
    //perlin_noise warp_noise(this->seed ^ 0x5F3173E9);
    perlin_noise forest_noise(this->seed ^ 0xF1271549);
    for (int i=0;i<32;i++) {
        for (int j=0;j<32;j++) {
            auto tile_x = static_cast<float>(i_chunk * 32 + i);
            auto tile_y = static_cast<float>(j_chunk * 32 + j);
            float elevation=elevation_noise.value2(tile_x/100,tile_y/100,2,0.2,7,0.5,2);
//            float warp_x=warp_noise.value2(tile_x*0.05,tile_y*0.05,2,0.02,2,0.5,2);
//            float warp_y=warp_noise.value2(tile_x*0.05+1000,tile_y*0.05+1000,2,0.02,2,0.5,2);
            float warp_x=0;
            float warp_y=0;
            float temperature=temperature_noise.value2(tile_x/1000+warp_x,tile_y/1000+warp_y,1,0.5,7,0.5,2);
            float aridity=aridity_noise.value2(tile_x/1000-warp_x,tile_y/1000+warp_y,1,0.5,7,0.5,2);
            //bool biome_1=temperature>0 && aridity<0;
            //bool biome_2=temperature<0 && aridity<0;
            //bool biome_3=(temperature>-1 && temperature<-0.3) && (aridity>0);
            //bool biome_4=(temperature>-0.3 && temperature<0.3) && (aridity>0);
            //bool biome_5=(temperature>0.3 && temperature<1) && (aridity>0) ;

            bool biome_3=(temperature>-1 && temperature<0) && (aridity<1 && aridity>0.3);
            bool biome_4=(temperature>0 && temperature<1) && (aridity<1 && aridity>0.3);
            bool biome_1=(temperature>-1 && temperature<1) && (aridity>-0.3 && aridity<0.3);
            bool biome_2=(temperature>-0.5 && temperature<1) && (aridity<-0.3 && aridity>-1);
            bool biome_5=(temperature>-1 && temperature<-0.5) && (aridity<-0.3 && aridity>-1);
            ground[i*32+j]=(elevation>-0.5)*(1*biome_1+2*biome_2+3*biome_3+(floor(seededRand(i,j,this->seed)*16)+20)*biome_4+5*biome_5);
            float ore=ore_noise.value2(tile_x/64,tile_y/64,1,0.7,6,0.5,2);
            float ore2=ore_noise2.value2(tile_x/64,tile_y/64,1,0.75,6,0.5,2);
            int decided_ore = 0;

            if (ore > 0.38f) {
                if (ore2 < -0.38f) {
                    decided_ore = 6;
                }
                else if (ore2 > 0.38f){
                    decided_ore = 7;
                }
            }
            else if (ore < -0.38f) {
                if (ore2 < -0.38f) {
                    decided_ore = 8;
                }
            }

            float forest=forest_noise.value2(tile_x/100,tile_y/100,1,0.4,3,0.5,2);
            decoratives[i*32+j]=40;
            if (decided_ore && ground[i*32+j] != 0) {
                decoratives[i*32+j]=decided_ore;
            }
            if (forest>0.3 && floor(seededRand(i,j,this->seed)*20) == 0 && ground[i*32+j] != 0) {
                decoratives[i*32+j]=9;
            }
            //decoratives[i*32+j]=(decided_ore && ground[i*32+j] != 0)?decided_ore:40;
        }
    }
}