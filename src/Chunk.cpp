//
// Created by Pete Downey on 2/10/24.
//

#include "Chunk.h"


#define TUP std::tuple<int, int, int>

/**
 * @brief Constructs a Chunk object with the given parameters.
 * 
 * @param x The x-coordinate of the chunk.
 * @param y The y-coordinate of the chunk.
 * @param size The size of the chunk.
 * @param defaultState The default state of the tiles in the chunk.
 * @param constraints The constraints for tile collapsing.
 * @param initCollapseTo What state to collapse the chunk to initially. If -1 it will collapse to a random state.
 */
Chunk::Chunk(const int x, const int y, const int size, const std::vector<float>& defaultState, const std::vector<Constraint>& constraints, int initCollapseTo) {

    this->state.resize(size, std::vector<std::shared_ptr<Tile>>(size));
    this->constraints = constraints;

    // TODO replace with fill
    for (int n = 0; n < size; n++) {
        for (int n2 = 0; n2 < size; n2++) {
            this->state[n][n2] = std::make_shared<Tile>(defaultState);
            //this->state[n][n2]->state = defaultState;
        }
    }

    this->defaultState = defaultState;
    this->chunkX = x;
    this->chunkY = y;
    this->size = size;
    this->initCollapse = initCollapseTo;
}

/**
 * @brief Gets the collapse status of the chunk.
 * 
 * @return true if the chunk is collapsed, false otherwise.
 */
bool Chunk::getCollapse() {
    return isChunkCollapsed;
}

/**
 * @brief Collapses the tiles in the chunk based on the constraints.
 * 
 * @param nearbyChunks The nearby chunks.
 * @param nearbyChunkCords The coordinates of the nearby chunks.
 * @return true if the chunk is successfully collapsed, false otherwise.
 */
bool Chunk::collapse(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords) {


    while (!allCollapsedCheck()) {

        bool stateCollapsed = false;
        do {
            
            stateCollapsed = false;

            //iterates through all tiles
            for (int tileX = 0; tileX < size; tileX++) {
                for (int tileY = 0; tileY < size; tileY++) {
 
                    //tile already collapsed skip
                    if (getTile(tileX, tileY)->collapsed) continue;

                    //goes through all constraints
                    for (int constraintIndex = 0; constraintIndex < constraints.size(); constraintIndex++) {

                        Type cType = constraints[constraintIndex].ConstraintType;

                        switch (cType) {
                            case RADIUS:

                                //iterates through radius
                                for (int x = -get<0>(constraints[constraintIndex].offsets[0]); x <= get<0>(constraints[constraintIndex].offsets[0]); x++) {
                                    for (int y = -get<0>(constraints[constraintIndex].offsets[0]); y <= get<0>(constraints[constraintIndex].offsets[0]); y++) {

                                        //checks if in radius .01 is for floating point error
                                        if (x*x + y*y - .01 > get<0>(constraints[constraintIndex].offsets[0])*get<0>(constraints[constraintIndex].offsets[0])) continue;

                                        //ensures not the same tile
                                        if (x == 0 && y == 0) continue;

                                        //checks if state collapsed
                                        Tile tile = getOtherChunksTile(nearbyChunks, nearbyChunkCords, tileX + x, tileY + y);
                                        if (tile.collapsedState == get<2>(constraints[constraintIndex].offsets[0])) {

                                            //collapses tile
                                            if (constraints[constraintIndex].collapseTo) {
                                                bool fullCollapsed = collapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                                if (fullCollapsed) stateCollapsed = true;
                                            } else {
                                                int fullCollapsed = partiallyCollapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                                if (fullCollapsed != -1) stateCollapsed = true;
                                            }
                                            break;
                                        }
                                    }
                                }
                                break;      
                            case SQUARE:

                                //iterates through square
                                for (int x = -get<0>(constraints[constraintIndex].offsets[0]); x <= get<0>(constraints[constraintIndex].offsets[0]); x++) {
                                    for (int y = -get<1>(constraints[constraintIndex].offsets[0]); y <= get<1>(constraints[constraintIndex].offsets[0]); y++) {

                                        //ensures not the same tile
                                        if (x == 0 && y == 0) continue;

                                        //checks if state collapsed
                                        Tile tile = getOtherChunksTile(nearbyChunks, nearbyChunkCords, tileX + x, tileY + y);
                                        if (tile.collapsedState == get<2>(constraints[constraintIndex].offsets[0])) {

                                            //collapses tile
                                            if (constraints[constraintIndex].collapseTo) {
                                                bool fullCollapsed = collapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                                if (fullCollapsed) stateCollapsed = true;
                                            } else {
                                                int fullCollapsed = partiallyCollapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                                if (fullCollapsed != -1) stateCollapsed = true;
                                            }
                                            break;
                                        }
                                    }
                                }
                                break;

                            case CORD: {
                                //if all cord constraints match up
                                bool fullMatch = true;
                                for (int term = 0; term < constraints[constraintIndex].offsets.size(); term++) {
                                    
                                    int x = tileX + get<0>(constraints[constraintIndex].offsets[term]);
                                    int y = tileY + get<1>(constraints[constraintIndex].offsets[term]);

                                    Tile tile = getOtherChunksTile(nearbyChunks, nearbyChunkCords, x, y);

                                    if (tile.state[0] == -1) {
                                        float tempRand = rand() / RAND_MAX;
                                        fullMatch = false; //rand() < defaultState[get<2>(constraints[constraintIndex].offsets[term])];
                                        if (!fullMatch) break;
                                    }
                                    if (tile.collapsedState != get<2>(constraints[constraintIndex].offsets[term])) {
                                        fullMatch = false;
                                        break;
                                    }
                                }
                                // if they do match up collapse
                                if (fullMatch) {
                                    if (constraints[constraintIndex].collapseTo) {
                                        bool fullCollapsed = collapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                        if (fullCollapsed) stateCollapsed = true;
                                    } else {
                                        int fullCollapsed = partiallyCollapseTile(getTile(tileX, tileY), constraints[constraintIndex].effectedState);
                                        if (fullCollapsed != -1) stateCollapsed = true;
                                    }
                                }
                                break;
                            }
                        }
                    }


                }
            }
        } while (stateCollapsed);
        
        if (!allCollapsedCheck())
            randomCollapse();
    }

    return true;
}

/**
 * @brief Checks if all tiles in the chunk are collapsed.
 * 
 * @return true if all tiles are collapsed, false otherwise.
 */
bool Chunk::allCollapsedCheck() {
    //itterates through all collapses
    int sum = 0;
    for (int n1 = 0; n1 < state.size(); n1++) {
        for (int n2 = 0; n2 < state[n1].size(); n2++) {
            sum += state[n1][n2]->collapsed;
        }
    }
    //if all are true returns true
    isChunkCollapsed = (sum == state.size()*state.size());
    return isChunkCollapsed;
}

// TODO add to collapsed list
/**
 * @brief Partially collapses a tile in the chunk.
 * 
 * @param tile The tile to be partially collapsed.
 * @param collapseToZero The state to collapse the tile to.
 * @return The collapsed state of the tile, or -1 if the tile cannot be partially collapsed.
 */
int Chunk::partiallyCollapseTile(std::shared_ptr<Tile> tile, int collapseToZero) {
       
       //checks if already collapsed
       if (tile->state.at(collapseToZero) == 1 || tile->collapsed) return -1;
       tile->state.at(collapseToZero) = 0;

        // if all zero
        float sum = 0;
        for (float n : tile->state) {
            sum += n;
        }
        if (sum == 0) return -1;

        //normalizes
        for (int n = 0; n < tile->state.size(); n++) {

            tile->state.at(n) /= sum;
            if (tile->state.at(n) > .999) {
                tile->collapsed = true;
                tile->collapsedState = n;
                return n;
            }
        }
        return -1;
}

//Dont have other chunks call
// seg fauls sometimes?
/**
 * @brief Gets the tile at the specified coordinates in the chunk.
 * 
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @return A shared pointer to the tile.
 */
std::shared_ptr<Tile> Chunk::getTile(int x, int y) {
    return state[x][y];
}

/**
 * @brief Gets a copy of the tile at the specified coordinates in the chunk.
 * 
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @return A copy of the tile.
 */
Tile Chunk::getTileCopy(int x, int y) {
    return *(state[x][y]);
}

/**
 * @brief Performs a random collapse on a tile in the chunk.
 * 
 * @return A tuple containing the collapsed tile's coordinates and state.
 */
std::tuple<int, int, int> Chunk::randomCollapse() {
    
    //TODO make this not awful
    bool valid = false;
    int x, y;

    int n = 0;

    while (!valid) {

        n++;
        if (n > 1000) {
            std::cout<<"random"<<std::endl;
            return TUP(-1, -1, -1);
        }
        x = (((double) rand() / (RAND_MAX)) * state.size());
        y = (((double) rand() / (RAND_MAX)) * state.size());

        valid = !getTile(x, y)->collapsed;
    }
    std::shared_ptr<Tile> tile = getTile(x, y);

    float random = ((double) rand() / (RAND_MAX));
    float sum = 0;

    //if it collapse is defined and that state is stil possible
    if (initCollapse != -1 && tile->state[initCollapse] != 0) {
        collapseTile(tile, initCollapse);
        return TUP(x, y, tile->collapsedState);
    }

    //collapse to a random state
    for (int n = 0; n < tile->state.size(); n++) {
        sum += tile->state[n];
        if (sum > random) {
            collapseTile(tile, n);
            return TUP(x, y, tile->collapsedState);
        }
    }
    //if it fails to collapse
    return TUP(x, y, tile->collapsedState);
}

/**
 * @brief Collapses a tile in the chunk to a specific state.
 * 
 * @param tile The tile to be collapsed.
 * @param collapseToOne The state to collapse the tile to.
 * @return true if the tile is successfully collapsed, false otherwise.
 */
bool Chunk::collapseTile(std::shared_ptr<Tile> tile, int collapseToOne) {

    //checks if state is zero
    if (tile->state[collapseToOne] == 0) return false;

    //sets all to zero
    std::fill(tile->state.begin(), tile->state.end(), 0);

    //collapses to one
    tile->state.at(collapseToOne) = 1;
    tile->collapsedState = collapseToOne;
    tile->collapsed = true;
    return true;
}

/**
 * @brief Collapses a tile in the chunk to a specific state.
 * 
 * @param collapseX The x-coordinate of the tile to be collapsed.
 * @param collapseY The y-coordinate of the tile to be collapsed.
 * @param collapseToOne The state to collapse the tile to.
 * @return true if the tile is successfully collapsed, false otherwise.
 */
bool Chunk::collapseTile(int collapseX, int collapseY, int collapseToOne) {
    return collapseTile(getTile(chunkX, chunkY), collapseToOne);
}

/**
 * @brief Gets the size of the chunk.
 * 
 * @return The size of the chunk.
 */
int Chunk::getSize() {return size;}

/**
 * @brief Gets a reference to the state of the chunk.
 * 
 * @return A reference to the state of the chunk.
 */
std::vector<std::vector<std::shared_ptr<Tile>>>& Chunk::getState() {
    return state;
}

/**
 * @brief Gets the location of the chunk.
 * 
 * @return A tuple containing the x and y coordinates of the chunk.
 */
std::tuple<int, int> Chunk::getLocation() {
    return {chunkX, chunkY};
}

/**
 * @brief Checks if the specified coordinates are within the chunk.
 * 
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return true if the coordinates are within the chunk, false otherwise.
 */
bool Chunk::withinChunk(int x, int y) {
    return (x >= 0 && x < size && y >= 0 && y < size);
}

/**
 * @brief Gets the tile from the nearby chunks at the specified coordinates.
 * 
 * @param nearbyChunks The nearby chunks.
 * @param nearbyChunkCords The coordinates of the nearby chunks.
 * @param xOffset The x-offset from the current chunk.
 * @param yOffset The y-offset from the current chunk.
 * @return The tile at the specified coordinates.
 */
Tile Chunk::getOtherChunksTile(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords, int xOffset, int yOffset) {

    //gets chunk and tile
    int chunkX = xOffset / size;
    int chunkY = yOffset / size;

    chunkX += xOffset < 0 ? -1 : 0;
    chunkY += yOffset < 0 ? -1 : 0;

    if (chunkX == 0 && chunkY == 0) return *getTile(xOffset, yOffset);

    int tileX = xOffset % size;
    int tileY = yOffset % size;

    tileX += tileX < 0 ? size : 0;
    tileY += tileY < 0 ? size : 0;

    //checks if chunk is in nearby chunks
    for (int n = 0; n < nearbyChunks.size(); n++) {
        auto [x, y] = nearbyChunkCords.at(n);
        if (x == chunkX && y == chunkY) {
            //returns a copy of the tile
            //if returns a pointer it segfaults for some reason
            return nearbyChunks[n]->getTileCopy(tileX, tileY);
        }
    }

    return Tile{std::vector<float>{-1}};
}