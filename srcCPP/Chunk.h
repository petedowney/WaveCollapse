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
    std::vector<std::tuple<int, int, int>> offsets;
    int effectedState{-1};
    bool collapseTo{false};
};

struct Tile : public std::enable_shared_from_this<Tile> {
    Tile(std::vector<float> state) : state(state), collapsed(false), collapsedState(-1) {}
    std::vector<float> state;
    bool collapsed=false;
    int collapsedState = -1;
};

class Chunk : public std::enable_shared_from_this<Chunk> {

public:
    Chunk(int x, int y, int size, const std::vector<float>& defaultState, const std::vector<Constraint>& constraints, int initCollapseTo=-1);
    //Chunk(int x, int y, int size, std::vector<float> defaultState, std::vector<Constraint> constraints);
    bool collapse(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords);

    std::shared_ptr<Tile> getTile(int x, int y);

    int getSize();
    std::tuple<int, int> getLocation();

    std::vector<std::vector<std::shared_ptr<Tile>>>& getState();

    bool getCollapse();

private:

    bool isChunkCollapsed = false;
    std::vector<std::vector<std::shared_ptr<Tile>>> state;
    std::vector<Constraint> constraints;
    int chunkX, chunkY, size;
    int initCollapse;

    Tile getTileCopy(int x, int y);

    std::vector<float> defaultState;

    bool allCollapsedCheck();
    int partiallyCollapseTile(std::shared_ptr<Tile> tile, int collapseToZero);

    bool withinChunk(int x, int y);

    std::tuple<int, int, int> randomCollapse();

    bool collapseTile(int collapseX, int collapseY, int state);
    bool collapseTile(std::shared_ptr<Tile> tile, int state);

    //split up the collapsing chunk into smaller funcs
    void collapseChunkCord(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords);
    void collapseChunkRadius(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords);
    void collapseChunkSquare(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords);

    Tile getOtherChunksTile(std::vector<std::shared_ptr<Chunk>> nearbyChunks, std::vector<std::tuple<int, int>> nearbyChunkCords, int xOffset, int yOffset);
};


#endif //WAVECOLLAPSE_CHUNK_H
