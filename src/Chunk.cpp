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

    this->defaultState = defaultState;
    this->chunkX = x;
    this->chunkY = y;
    this->size = size;
    this->initCollapse = initCollapseTo;
}

bool Chunk::getCollapse() {
    return isChunkCollapsed;
}

bool Chunk::collapse(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords) {

    //TODO multithread
    //begin collapsing
    

    bool isChunkCollapsed = false;

    while (!isChunkCollapsed) {

        bool stateCollapsed = false;
        do {
            
            stateCollapsed = false;

            for (int tileX = 0; tileX < size; tileX++) {
                for (int tileY = 0; tileY < size; tileY++) {
 
                    //tile already collapsed skip
                    if (getTile(tileX, tileY)->collapsed) continue;

                    //goes through all constraints
                    for (int constraintIndex = 0; constraintIndex < constraints.size(); constraintIndex++) {

                        Type cType = constraints[constraintIndex].ConstraintType;

                        switch (cType) {
                            case RADIUS:

                            case SQUARE:

                                break;

                            case CORD: {
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
        
        isChunkCollapsed = allCollapsedCheck();

        if (!isChunkCollapsed)
            randomCollapse();
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
       
       if (tile->state.at(collapseToZero) == 1 || tile->collapsed) return -1;
       tile->state.at(collapseToZero) = 0;

        float sum = 0;
        for (float n : tile->state) {
            sum += n;
        }
        if (sum == 0) return -1;

        int loop = 0;

        for (int n = 0; n < tile->state.size(); n++) {

            loop++;
            if (loop > 1000) {
                std::cout<<"loop"<<std::endl;
                return -1;
            }
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
std::shared_ptr<Tile> Chunk::getTile(int x, int y) {
    return state[x][y];
}

Tile Chunk::getTileCopy(int x, int y) {
    return *(state[x][y]);
}


std::tuple<int, int, int> Chunk::randomCollapse() {
    
    //TODO make this not awful
    bool valid = false;
    int x, y;

    int n = 0;

    while (!valid) {

        n++;
        std::cout<<"random "<< n << std::endl;
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

bool Chunk::collapseTile(std::shared_ptr<Tile> tile, int collapseToOne) {

    if (tile->state[collapseToOne] == 0) return false;
    std::fill(tile->state.begin(), tile->state.end(), 0);
    tile->state.at(collapseToOne) = 1;
    tile->collapsedState = collapseToOne;
    tile->collapsed = true;
    return true;
}

bool Chunk::collapseTile(int collapseX, int collapseY, int collapseToOne) {
    return collapseTile(getTile(chunkX, chunkY), collapseToOne);
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


Tile Chunk::getOtherChunksTile(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords, int xOffset, int yOffset) {

    int chunkX = xOffset / size;
    int chunkY = yOffset / size;

    chunkX += xOffset < 0 ? -1 : 0;
    chunkY += yOffset < 0 ? -1 : 0;

    if (chunkX == 0 && chunkY == 0) return *getTile(xOffset, yOffset);

    int tileX = xOffset % size;
    int tileY = yOffset % size;

    tileX += tileX < 0 ? size : 0;
    tileY += tileY < 0 ? size : 0;

    //TODO make this not awful
    for (int n = 0; n < nearbyChunks.size(); n++) {
        auto [x, y] = nearbyChunkCords.at(n);
        if (x == chunkX && y == chunkY) {

            return nearbyChunks[n]->getTileCopy(tileX, tileY);
        }
    }

    return Tile{std::vector<float>{-1}};
}