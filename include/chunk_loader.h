//
// Created by stefa on 3/16/2026.
//

#ifndef OOP_CHUNK_LOADER_H
#define OOP_CHUNK_LOADER_H
#include "world_generator.h"
#include "chunk.h"
#include <map>
#include <string>


class chunk_loader {
    world_generator generator;
    std::map<std::string, chunk> chunk_cache;
    public:
        chunk_loader(world_generator &generator);
        chunk* get_chunk(int chunk_i,int chunk_j);
};


#endif //OOP_C HUNK_LOADER_H

