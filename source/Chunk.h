//
// Created by Pete Downey on 2/10/24.
//

#ifndef WAVECOLLAPSE_CHUNK_H
#define WAVECOLLAPSE_CHUNK_H


#include <vector>
#include <queue>
#include <iostream>

enum Type {CORD, RADIUS, SQUARE};

struct Constraint {
    Type ConstraintType{CORD};
    int causingState{};
    int effectedState{0};
    std::vector<int> miscArgs;
};

struct Tile {
    std::vector<float> state;
    bool collapsed=false;
};

class Chunk {

public:
    Chunk(int x, int y, int size, const std::vector<float>& defaultState, const std::vector<Constraint>& constraints);
    bool collapse();

    Tile* getTile(int x, int y);
    int getSize();

    void collapseTile(int collapseX, int collapseY, int state);
    void collapseTile(Tile* tile, int state);

private:
    bool isChunkCollapsed = false;
    std::vector<std::vector<Tile>> state;
    std::vector<Constraint> constraints;
    int x, y, size;

    bool allCollapsedCheck();
    int partiallyCollapseTile(Tile* tile, int collapseToZero);

    std::tuple<int, int, int> randomCollapse();
};


#endif //WAVECOLLAPSE_CHUNK_H
