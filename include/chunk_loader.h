//
// Created by stefa on 3/16/2026.
//

#ifndef OOP_CHUNK_LOADER_H
#define OOP_CHUNK_LOADER_H
#include "world_generator.h"
#include "chunk.h"
#include <unordered_map>
#include <string>
#include <future>

class chunk_loader {
    world_generator generator;
    std::unordered_map<std::string, chunk> chunk_cache;
    std::unordered_map<std::string, std::future<chunk>> pending_chunks;
    public:
        chunk* get_chunk(int chunk_i,int chunk_j);
        int peak_tile(int i,int j);
        void add_building(int id,int x,int y);
};


#endif //OOP_CHUNK_LOADER_H
