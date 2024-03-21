//
// Created by Pete Downey on 2/10/24.
//

#include "WaveCollapse.h"

#include <utility>

WaveCollapse::WaveCollapse(std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize) {

    this->STDStates = std::move(STDStates);
    this->constraints = std::move(constraints);
    this->size = chunkSize;

}

void WaveCollapse::GenerateChunk(int x, int y, bool collapse) {
    //TODO replace with 2d hash
    if (chunkMap.contains(x) && chunkMap[x].contains(y)) return;

    auto* chunk = new Chunk(x, y, size, STDStates, constraints);

    if (collapse) collapseChunk(chunk);

    std::pair<int, Chunk> yCord {y,*chunk};
    delete chunk;
    if (chunkMap.contains(x)) {
        chunkMap[x].insert(yCord);
        return;
    }
    std::unordered_map<int, Chunk> xMap;
    xMap.insert(yCord);
    std::pair<int, std::unordered_map<int, Chunk>> xCord {x, xMap};
    chunkMap.insert(xCord);
}

//can access via python
void WaveCollapse::collapseChunk(int x, int y) {
    if (chunkMap.contains(x) && chunkMap[x].contains(y)) {
        collapseChunk(&chunkMap[x].at(y));
    }
}

//cant access via python
void WaveCollapse::collapseChunk(Chunk* chunk) {
    chunk->collapse();
}

void WaveCollapse::setSeed(int seed) {std::srand(seed);}

Chunk* WaveCollapse::getChunk(int x, int y) {
    return &(chunkMap[x].at(y));
}

int WaveCollapse::getChunkSize() {
    return size;
}

