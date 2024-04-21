//
// Created by Pete Downey on 2/10/24.
//

#include "Chunk.h"


#define TUP std::tuple<int, int, int>

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


    this->chunkX = x;
    this->chunkY = y;
    this->size = size;
    this->initCollapse = initCollapseTo;
}

bool Chunk::getCollapse() {
    return isChunkCollapsed;
}

bool Chunk::collapse(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords) {
    
    std::queue<TUP> flagged;

    // chunking logic
    if (!nearbyChunks.empty()) {

        for (int n = 0; n < nearbyChunks.size(); n++) {
            if (nearbyChunks[n]->getCollapse()) {
                
                auto [xOffset, yOffset] = nearbyChunkCords[n];
                xOffset *= size;
                yOffset *= size;

                auto nearbyChunksState = nearbyChunks[n]->getState();

                for (int tileX = 0; tileX < size; tileX++) {
                    for (int tileY = 0; tileY < size; tileY++) {

                        flagged.emplace(TUP(xOffset+tileX, yOffset+tileY, nearbyChunksState[tileX][tileY]->collapsedState));
                    }
                }
            }
            //flagged.emplace()
        }
    }

    //begin collapsing
    while (!isChunkCollapsed) {

        int nextX, nextY;
        int nextTile;

        int sum = 0;
        for (int n1 = 0; n1 < state.size(); n1++) {
            for (int n2 = 0; n2 < state[n1].size(); n2++) {
                sum += state[n1][n2]->collapsed;
            }
        }
        // if queue is empty collapses tile and adds to queue
        if (flagged.empty()) {
            if (allCollapsedCheck()) return true;
            flagged.emplace(randomCollapse());
        // pops out a val from queu
        } else {
            auto [a, b, c] = flagged.front();
            nextX = a;
            nextY = b;
            nextTile = c;
            flagged.pop();
        }
        //collapses other tiles based off of constraints
        for (int n = 0; n < constraints.size(); n++) {
            Type cType = constraints[n].ConstraintType;
            if (constraints[n].causingState == nextTile) {
                switch (cType) {
                    case RADIUS:
                        
                        int radius = constraints[n].miscArgs[0];
                        for (int squareX = 0; squareX < radius; squareX++) {
                            for (int squareY = 0; squareY < radius; squareY++) {

                                int distance = abs(squareX - nextX) + abs(squareY - nextY);

                                if (distance <= constraints[n].miscArgs[0] && withinChunk(squareX+nextX, squareY+nextY)) {
                                    std::shared_ptr<Tile> tile = getTile(squareX+nextX, squareY+nextY);
                                    if (!tile->collapsed) {
                                        if (constraints[n].collapseTo) {
                                            collapseTile(tile, constraints[n].effectedState);
                                            flagged.emplace(TUP(squareX+nextX, squareY+nextY, tile->collapsedState));
                                        } else {
                                            int collapsedIndex = partiallyCollapseTile(tile, constraints[n].effectedState);
                                            if (collapsedIndex != -1) flagged.emplace(TUP(squareX+nextX, squareY+nextY, tile->collapsedState));
                                        }
                                    }
                                }
                            }
                        }
                        break;

                    case SQUARE:
                        
                        int radius = constraints[n].miscArgs[0];
                        for (int squareX = 0; squareX < radius; squareX++) {
                            for (int squareY = 0; squareY < radius; squareY++) {

                                int distance = abs(squareX - nextX) + abs(squareY - nextY);

                                if (withinChunk(squareX+nextX, squareY+nextY)) {
                                    std::shared_ptr<Tile> tile = getTile(squareX+nextX, squareY+nextY);
                                    if (!tile->collapsed) {
                                        if (constraints[n].collapseTo) {
                                            collapseTile(tile, constraints[n].effectedState);
                                            flagged.emplace(TUP(squareX+nextX, squareY+nextY, tile->collapsedState));
                                        } else {
                                            int collapsedIndex = partiallyCollapseTile(tile, constraints[n].effectedState);
                                            if (collapsedIndex != -1) flagged.emplace(TUP(squareX+nextX, squareY+nextY, tile->collapsedState));
                                        }
                                    }
                                }
                            }
                        }
                        break;

                    case CORD: {
                        
                        //gets relative cords
                        int tileX = nextX + constraints[n].miscArgs[0];
                        int tileY = nextY + constraints[n].miscArgs[1];
                        
                        //if within the chunk
                        if (withinChunk(tileX, tileY)) {

                            std::shared_ptr<Tile> tile = getTile(tileX, tileY);

                            //checks if collapsed
                            if (!tile->collapsed) {
                                
                                if (constraints[n].collapseTo) {
                                    collapseTile(tile, constraints[n].effectedState);
                                    flagged.emplace(TUP(tileX, tileY, tile->collapsedState));
                                } else {
                                    int collapsedIndex = partiallyCollapseTile(tile, constraints[n].effectedState);
                                    if (collapsedIndex != -1) flagged.emplace(TUP(tileX, tileY, tile->collapsedState));
                                }
                            }        
                        }
                        break;
                    }

                    case CCORD: {
                        

                    }

                    break;
                }
            }
        }
    }

    return true;
}


bool Chunk::allCollapsedCheck() {
    int sum = 0;
    for (int n1 = 0; n1 < state.size(); n1++) {
        for (int n2 = 0; n2 < state[n1].size(); n2++) {
            sum += state[n1][n2]->collapsed;
        }
    }

    isChunkCollapsed = (sum == state.size()*state.size());
    return isChunkCollapsed;
}

// TODO add to collapsed list
int Chunk::partiallyCollapseTile(std::shared_ptr<Tile> tile, int collapseToZero) {
        tile->state.at(collapseToZero) = 0;
        float sum = 0;
        for (float n : tile->state) {
            sum += n;
        }
        if (sum == 0) return -1;
        for (int n = 0; n < tile->state.size(); n++) {
            tile->state.at(n) /= sum;
            if (1 - tile->state.at(n) < .0001) {
                tile->collapsed = true;
                tile->collapsedState = n;
                return n;
            }
        }
        return -1;
}

std::shared_ptr<Tile> Chunk::getTile(int x, int y) {
    return state[x][y];
}

std::tuple<int, int, int> Chunk::randomCollapse() {
    
    //TODO make this not awful
    bool valid = false;
    int x, y;
    while (!valid) {
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

void Chunk::collapseTile(std::shared_ptr<Tile> tile, int collapseToOne) {
    std::fill(tile->state.begin(), tile->state.end(), 0);
    tile->state.at(collapseToOne) = 1;
    tile->collapsedState = collapseToOne;
    tile->collapsed = true;
}

void Chunk::collapseTile(int collapseX, int collapseY, int collapseToOne) {
    collapseTile(getTile(chunkX, chunkY), collapseToOne);
}

int Chunk::getSize() {return size;}

//TODO check if seg
std::vector<std::vector<std::shared_ptr<Tile>>>& Chunk::getState() {
    return state;
}

std::tuple<int, int> Chunk::getLocation() {
    return {chunkX, chunkY};
}

bool Chunk::withinChunk(int x, int y) {
    return (x >= 0 && x < size && y >= 0 && y < size);
}


std::shared_ptr<Tile> Chunk::getOtherChunksTile(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords, int xOffset, int yOffset) {

    int chunkX = xOffset / size;
    int chunkY = yOffset / size;

    chunkX += xOffset < 0 ? -1 : 0;
    chunkY += yOffset < 0 ? -1 : 0;

    int tileX = xOffset % size;
    int tileY = yOffset % size;

    tileX = tileX < 0 ? size : tileX;
    tileY = tileY < 0 ? size : tileX;

    //TODO make this not awful
    for (int n = 0; n < nearbyChunks.size(); n++) {
        auto [x, y] = nearbyChunks[n]->getLocation();
        if (x == chunkX && y == chunkY) {
            return nearbyChunks[n]->getTile(tileX, tileY);
        }
    }

}