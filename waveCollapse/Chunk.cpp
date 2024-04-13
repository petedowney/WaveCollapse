//
// Created by Pete Downey on 2/10/24.
//

#include "Chunk.h"


#define intTuple std::tuple<int, int, int>

Chunk::Chunk(const int x, const int y, const int size, const std::vector<float>& defaultState, const std::vector<Constraint>& constraints) {

    this->state.resize(size, std::vector<Tile>(size));
    this->constraints = constraints;

    // TODO replace with fill
    for (int n = 0; n < size; n++) {
        for (int n2 = 0; n2 < size; n2++) {
            this->state[n][n2].state = defaultState;
        }
    }
    this->chunkX = x;
    this->chunkY = y;
    this->size = size;
}

bool Chunk::collapse(std::vector<Chunk*> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords) {
    std::queue<intTuple> flagged;

    if (!nearbyChunks.empty()) {

        std::cout << "--------" << std::endl;
        for (int n = 0; n < nearbyChunks.size(); n++) {
            auto [xOffset, yOffset] = nearbyChunkCords[n];
            xOffset *= size;
            yOffset *= size;

            std::cout << "off" << xOffset << " " << yOffset << std::endl;

            for (int tileX = 0; tileX < size; tileX++) {
                for (int tileY = 0; tileY < size; tileY++) {
                    int state = nearbyChunks[n]->getCollapsedTileState(nearbyChunks[n]->getTile(tileX, tileY));

                    std::cout << "off" << xOffset+tileX << " " << yOffset+tileY << std::endl;
                    flagged.emplace(intTuple(state, xOffset+tileX, yOffset+tileY));
                }
            }
            //flagged.emplace()
        }
    }
    std::cout << flagged.size() << std::endl;
    //int counter = 0;
    while (!isChunkCollapsed) {

        //while (counter > 100) {};
        //counter+=1;

        int currentX, currentY, collapsedTileState;

        int sum = 0;
        for (int n1 = 0; n1 < state.size(); n1++) {
            for (int n2 = 0; n2 < state[n1].size(); n2++) {
                sum += state[n1][n2].collapsed;
            }
        }

        if (flagged.empty()) {
            if (allCollapsedCheck()) return true;
            auto [a, b, c] = randomCollapse();
            currentX = a;
            currentY = b;
            collapsedTileState = c;
            flagged.emplace(intTuple(a, b, c));
        } else {
            auto [a, b, c] = flagged.front();
            currentX = a;
            currentY = b;
            collapsedTileState = c;
            flagged.pop();
        }
        for (int n = 0; n < constraints.size(); n++) {
            Type cType = constraints[n].ConstraintType;
            if (constraints[n].causingState == collapsedTileState) {
                switch (cType) {
                    case RADIUS:
                        break;
                    case SQUARE:
                        break;
                    case CORD: {

                        int tileX = currentX + constraints[n].miscArgs[0];
                        int tileY = currentY + constraints[n].miscArgs[1];

                        if (tileX >= 0 && tileX < state.size() &&
                                tileY >= 0 && tileY < state.size()) {

                            Tile *tile = getTile(tileX, tileY);

                            if (!tile->collapsed) {
                                //TODO cleanup
                                int collapsedIndex = partiallyCollapseTile(tile, constraints[n].effectedState);

                                if (collapsedIndex != -1) flagged.emplace(intTuple(tileX, tileY, collapsedIndex));
                            }
                        }
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
            sum += state[n1][n2].collapsed;
        }
    }

    isChunkCollapsed = (sum == state.size()*state.size());
    return isChunkCollapsed;
}

// TODO add to collapsed list
int Chunk::partiallyCollapseTile(Tile *tile, int collapseToZero) {
        tile->state.at(collapseToZero) = 0;
        float sum = 0;
        for (float n : tile->state) {
            sum += n;
        }
        if (sum == 0) return -1;
        for (int n = 0; n < tile->state.size(); n++) {
            tile->state.at(n) /= sum;
            if (1 - tile->state.at(n) < .001) {
                tile->collapsed = true;
                return n;
            }
        }
        return -1;
}

Tile* Chunk::getTile(int x, int y) {
    return &state[x][y];
}

std::tuple<int, int, int> Chunk::randomCollapse() {
    bool valid = false;
    int x, y;
    while (!valid) {
        x = (((double) rand() / (RAND_MAX)) * state.size());
        y = (((double) rand() / (RAND_MAX)) * state.size());

        valid = !getTile(x, y)->collapsed;
    }
    Tile* tile = getTile(x, y);

    float random = ((double) rand() / (RAND_MAX));
    float sum = 0;

    for (int n = 0; n < tile->state.size(); n++) {
        sum += tile->state[n];
        if (sum > random) {
            collapseTile(tile, n);
            return std::tuple<int, int, int>(x, y, n);
        }
    }
    return std::tuple<int, int, int>(x, y, -1);
}

void Chunk::collapseTile(Tile* tile, int collapseToOne) {
    std::fill(tile->state.begin(), tile->state.end(), 0);
    tile->state.at(collapseToOne) = 1;
    tile->collapsed = true;
}

void Chunk::collapseTile(int collapseX, int collapseY, int collapseToOne) {
    collapseTile(getTile(chunkX, chunkY), collapseToOne);
}

int Chunk::getSize() {return size;}

int Chunk::getCollapsedTileState(int x, int y) {
    getCollapsedTileState(&state[x][y]);
}
int Chunk::getCollapsedTileState(Tile* tile) {
    for (int n = 0; n < tile->state.size(); n++) {
        if (tile->state[n] > .999) return n;
    }
    return -1;
}

std::tuple<int, int> Chunk::getLocation() {
    return {chunkX, chunkY};
}



