//
// Created by Pete Downey on 2/10/24.
//

#ifndef WAVECOLLAPSE_CHUNK_H
#define WAVECOLLAPSE_CHUNK_H


#include <vector>
#include <queue>
#include <iostream>
#include <memory>

enum Type {CORD, RADIUS, SQUARE};

struct Constraint {
    Type ConstraintType{CORD};
    int causingState{};
    int effectedState{0};
    std::vector<int> miscArgs;
};

struct Tile : public std::enable_shared_from_this<Tile> {
    Tile(std::vector<float> state, bool collapsed) : state(state), collapsed(collapsed) {}
    std::vector<float> state;
    bool collapsed=false;
};

class Chunk : public std::enable_shared_from_this<Chunk> {

public:
    Chunk(int x, int y, int size, const std::vector<float>& defaultState, const std::vector<Constraint>& constraints);
    //Chunk(int x, int y, int size, std::vector<float> defaultState, std::vector<Constraint> constraints);
    bool collapse(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords);

    std::shared_ptr<Tile> getTile(int x, int y);

    //TODO probably just add in an extra var
    int getCollapsedTileState(int x, int y);
    int getCollapsedTileState(std::shared_ptr<Tile> tile);

    int getSize();
    std::tuple<int, int> getLocation();

private:
    bool isChunkCollapsed = false;
    std::vector<std::vector<std::shared_ptr<Tile>>> state;
    std::vector<Constraint> constraints;
    int chunkX, chunkY, size;

    bool allCollapsedCheck();
    int partiallyCollapseTile(std::shared_ptr<Tile> tile, int collapseToZero);

    std::tuple<int, int, int> randomCollapse();

    void collapseTile(int collapseX, int collapseY, int state);
    void collapseTile(std::shared_ptr<Tile> tile, int state);
};


#endif //WAVECOLLAPSE_CHUNK_H
