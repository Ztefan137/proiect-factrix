//
// Created by stefa on 3/16/2026.
//

#include "../include/chunk_loader.h"
#include "chunk.h"
#include <unordered_map>
#include <string>
#include <future>
#include <cmath>
#include <iostream>

chunk* chunk_loader::get_chunk(int chunk_i, int chunk_j) {
    const std::string cache_key=std::to_string(chunk_i) + "," + std::to_string(chunk_j);
    auto cached_chunk = this->chunk_cache.find(cache_key);
    if (cached_chunk != chunk_cache.end()) {
        chunk *loaded_chunk = &cached_chunk->second;
        return loaded_chunk;
    }
    auto pending_chunk = pending_chunks.find(cache_key);
    if (pending_chunk != pending_chunks.end()) {
        auto& future_chunk=pending_chunk->second;
        if (future_chunk.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            chunk loaded_chunk = future_chunk.get();
            chunk_cache[cache_key] = std::move(loaded_chunk);
            pending_chunks.erase(pending_chunk);
            return &chunk_cache[cache_key];
        }
        return nullptr;
    }
    pending_chunks[cache_key] = std::async(std::launch::async, [=, this] {
        chunk c(chunk_i, chunk_j, this->generator,64.f,true);
        c.compute_va();
        return c;
    });

    return nullptr;
}

int chunk_loader::peak_tile(int x, int y) {
    const int chunk_size = 32;
    int chunk_i = static_cast<int>(std::floor(static_cast<float>(x) / chunk_size));
    int chunk_j = static_cast<int>(std::floor(static_cast<float>(y) / chunk_size));
    int local_x = x - (chunk_i * chunk_size);
    int local_y = y - (chunk_j * chunk_size);
    std::string cache_key = std::to_string(chunk_j) + "," + std::to_string(chunk_i);
    auto it = chunk_cache.find(cache_key);
    if (it != chunk_cache.end()) {
        return it->second.peak_tile(local_x, local_y);
    }
    return 0;
}

void chunk_loader::add_building(int id,int x, int y) {
    const int chunk_size = 32;
    int chunk_i = static_cast<int>(std::floor(static_cast<float>(x) / chunk_size));
    int chunk_j = static_cast<int>(std::floor(static_cast<float>(y) / chunk_size));
    int local_x = x - (chunk_i * chunk_size);
    int local_y = y - (chunk_j * chunk_size);
    std::string cache_key = std::to_string(chunk_j) + "," + std::to_string(chunk_i);
    auto it = chunk_cache.find(cache_key);
    if (it != chunk_cache.end()) {
        it->second.add_building(id,local_x,local_y);
    }
}
