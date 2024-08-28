//
// Created by Pete Downey on 2/10/24.
//

#include "WaveCollapse.h"

#include <utility>

/**
 * Constructor for the WaveCollapse class.
 * 
 * @param STDStates The vector of standard states.
 * @param constraints The vector of constraints.
 * @param chunkSize The size of the chunk.
 * @param initCollapse The initial collapse value.
 */
WaveCollapse::WaveCollapse(std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize, int initCollapse) {
    
    this->STDStates = std::move(STDStates);
    this->constraints = std::move(constraints);
    this->size = chunkSize;
    this->initCollapse = initCollapse;
}

/**
 * Generates a chunk at the specified coordinates.
 * 
 * @param x The x-coordinate of the chunk.
 * @param y The y-coordinate of the chunk.
 * @param collapse Whether to collapse the chunk or not.
 */
void WaveCollapse::GenerateChunk(int x, int y, bool collapse) {

    //if already exists
    if (chunkMap.contains(x) && chunkMap[x].contains(y)) return;

    //creates it
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(x, y, size, STDStates, constraints, initCollapse);

    //collapses it
    if (collapse) collapseChunk(chunk);

    //adds it to the map
    std::pair<int, std::shared_ptr<Chunk>> yCord {y, chunk};
    if (chunkMap.contains(x)) {
        chunkMap[x].insert(yCord);
        return;
    }

    std::unordered_map<int, std::shared_ptr<Chunk>> xMap;
    xMap.insert(yCord);
    std::pair<int, std::unordered_map<int, std::shared_ptr<Chunk>>> xCord {x, xMap};
    chunkMap.insert(xCord);
}

/**
 * Checks if a chunk exists at the specified coordinates.
 * 
 * @param x The x-coordinate of the chunk.
 * @param y The y-coordinate of the chunk.
 * @return True if the chunk exists, false otherwise.
 */

bool WaveCollapse::containsChunk(int x, int y) {
    return (chunkMap.contains(x) && chunkMap[x].contains(y));
}

/**
 * Collapses the chunk at the specified coordinates.
 * 
 * @param x The x-coordinate of the chunk.
 * @param y The y-coordinate of the chunk.
 */
void WaveCollapse::collapseChunk(int x, int y) {
    if (chunkMap.contains(x) && chunkMap[x].contains(y)) {
        collapseChunk(chunkMap[x].at(y));
    }
}

/**
 * Collapses the specified chunk.
 * 
 * @param chunk The chunk to be collapsed.
 */
void WaveCollapse::collapseChunk(std::shared_ptr<Chunk> chunk) {

    std::vector<std::shared_ptr<Chunk>> nearbyChunks = {};
    std::vector<std::tuple<int, int>> nearbyChunkCords = {};

    auto [chunkX, chunkY] = chunk->getLocation();

    for (int xOffset = - 1; xOffset <= 1; xOffset++) {
        for (int yOffset = -1; yOffset <= 1; yOffset++) {
            if (containsChunk(xOffset + chunkX, yOffset + chunkY) && (xOffset != 0 || yOffset != 0)) {
                nearbyChunks.emplace_back(getChunk(xOffset + chunkX, yOffset + chunkY));
                nearbyChunkCords.emplace_back(std::tuple<int, int>{xOffset, yOffset});
            }
        }
    }
    
    chunk->collapse(nearbyChunks, nearbyChunkCords);
}

/**
 * Sets the seed for the random number generator.
 * 
 * @param seed The seed value.
 */
void WaveCollapse::setSeed(int seed) {
    std::srand(seed);
}

/**
 * Gets the chunk at the specified coordinates.
 * 
 * @param x The x-coordinate of the chunk.
 * @param y The y-coordinate of the chunk.
 * @return The chunk at the specified coordinates.
 */
std::shared_ptr<Chunk> WaveCollapse::getChunk(int x, int y) {
    return (chunkMap[x].at(y));
}

/**
 * Gets the size of the chunk.
 * 
 * @return The size of the chunk.
 */
int WaveCollapse::getChunkSize() {
    return size;
}

//TODO: Implement the addAntiConstraints function.
void WaveCollapse::addAntiConstraints() {
    /**
     * Adds anti-constraints to the existing constraints.
     * 
     * TODO: Implement this function.
     */
    /*//TODO check if anticonstraint already exists
    int origConstraintLength = constraints.size();

    for (int n = 0; n < origConstraintLength; n++) {
        Constraint constraint = constraints.at(n);
        Constraint antiConstraint;
        switch (constraint.ConstraintType) {
            case CORD: {
                int xOffset = -constraint.miscArgs[0];
                int yOffset = -constraint.miscArgs[1];
                int effected = constraint.causingState;
                int causing = constraint.effectedState;
                antiConstraint = Constraint{CORD, causing, effected, {xOffset, yOffset}};
            }
                break;
            case RADIUS:
                antiConstraint = constraint; // TODO imp
                break;
            case SQUARE:
                antiConstraint = constraint;// TODO imp
                break;
        }
        constraints.emplace_back(antiConstraint);
    }*/
}

