//
// Created by Pete Downey on 2/10/24.
//

#ifndef WAVECOLLAPSE_WAVECOLLAPSE_H
#define WAVECOLLAPSE_WAVECOLLAPSE_H

#include <vector>
#include <unordered_map>
#include <tuple>

#include "Chunk.h"


class WaveCollapse {

public:
    WaveCollapse(std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize);

    void GenerateChunk(int x, int y, bool collapse=true);
    void collapseChunk(int x, int y);
    void collapseChunk(Chunk* chunk);

    static void setSeed(int seed);

    Chunk* getChunk(int x, int y);
    int getChunkSize();

private:
    std::unordered_map <int, std::unordered_map<int, Chunk>> chunkMap;
    int size;
    std::vector<float> STDStates;
    std::vector<Constraint> constraints;
};



#endif //WAVECOLLAPSE_WAVECOLLAPSE_H
