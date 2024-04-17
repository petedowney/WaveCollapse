//
// Created by Pete Downey on 2/10/24.
//

#ifndef WAVECOLLAPSE_WAVECOLLAPSE_H
#define WAVECOLLAPSE_WAVECOLLAPSE_H

#include <vector>
#include <unordered_map>
#include <tuple>

#include "Chunk.h"
#include <Python.h>


class WaveCollapse : public std::enable_shared_from_this<WaveCollapse>{

public:
    WaveCollapse(std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize);

    void GenerateChunk(int x, int y, bool collapse=true);
    bool containsChunk(int x, int y);
    void collapseChunk(int x, int y);
    void collapseChunk(std::shared_ptr<Chunk> chunk);

    static void setSeed(int seed);

    std::shared_ptr<Chunk> getChunk(int x, int y);
    int getChunkSize();

private:
    std::unordered_map <int, std::unordered_map<int, std::shared_ptr<Chunk>>> chunkMap;
    int size;
    std::vector<float> STDStates;
    std::vector<Constraint> constraints;
    void addAntiConstraints();
};



#endif //WAVECOLLAPSE_WAVECOLLAPSE_H
