//
// Created by stefa on 3/16/2026.
//

#include "../include/chunk_loader.h"
#include "world_generator.h"
#include "chunk.h"
#include <map>
#include <string>

chunk_loader::chunk_loader(world_generator &generator) {
    this->generator=generator;
}

chunk* chunk_loader::get_chunk(int chunk_i, int chunk_j) {
    const std::string cache_key=std::to_string(chunk_i) + "," + std::to_string(chunk_j);
    auto it = this->chunk_cache.find(cache_key);
    if (it != chunk_cache.end()) {
        chunk *loaded_chunk = &it->second;
        return loaded_chunk;
    } else {
        chunk new_chunk(chunk_i,chunk_j,this->generator,true);
        new_chunk.compute_va();
        this->chunk_cache[cache_key]=new_chunk;
        return &this->chunk_cache[cache_key];
    }
}