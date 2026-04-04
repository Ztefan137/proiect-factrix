//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_WORLD_GENERATOR_H
#define OOP_WORLD_GENERATOR_H


class world_generator {
    int seed=12;
public:
    void set_seed(int seed);
    void generate_chunk(int i,int j,int ground[],int decoratives[]) const;
};


#endif //OOP_WORLD_GENERATOR_H