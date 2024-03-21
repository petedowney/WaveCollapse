#include <iostream>
#include "raylib-cpp.hpp"
#include <cstdlib>
#include "WaveCollapse.h"
#include "Chunk.h"

void update();
void render();

Vector2 mousePos;
Vector2 screenDimensions = {1000, 1000};
Vector2 pixelDimensions = {250, 250};

Vector2 ratio = {screenDimensions.x / pixelDimensions.x, screenDimensions.y / pixelDimensions.y};

bool debug = false;

//std::vector<float> STDStates, std::vector<Constraint> constraints, int chunkSize

std::vector<Constraint> constraints;
WaveCollapse* waveCollapse;
Chunk* chunk;

int main() {


    constraints.emplace_back( Constraint{CORD, 1, 0, {1, -1}});
    constraints.emplace_back( Constraint{CORD, 1, 0, {-1, -1}});
    //constraints.emplace_back( Constraint{CORD, 1, 1, {0, -1}});
    //constraints.emplace_back( Constraint{CORD, 1, 1, {1, 0}});
    //constraints.emplace_back( Constraint{CORD, 1, 1, {-1, 0}});

    //constraints.emplace_back( Constraint{CORD, 0, 0, {0, 1}});
    //constraints.emplace_back( Constraint{CORD, 0, 0, {0, -1}});
    //constraints.emplace_back( Constraint{CORD, 0, 0, {1, 0}});
    //constraints.emplace_back( Constraint{CORD, 0, 0, {-1, 0}});
    std::cout << "a" << std::endl;



    waveCollapse = new WaveCollapse(std::vector<float>{.95, .05} ,constraints,10);
    std::cout << "b" << std::endl;
    waveCollapse->GenerateChunk(0,0);
    std::cout << "c" << std::endl;
    chunk = waveCollapse->getChunk(0, 0);

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    raylib::Window window(screenDimensions.x, screenDimensions.y, "Test");

    SetTargetFPS(60);

    while (!window.ShouldClose()) {

        BeginDrawing();

        window.ClearBackground(BLACK);

        update();
        render();

        EndDrawing();
    }

    return 0;
}

void update() {
    mousePos = GetMousePosition();

    if (IsKeyPressed(KEY_P)) {
        debug = !debug;
    }
}

void render() {

    DrawCircle(mousePos.x, mousePos.y, 5, RED);

    for (int x = 0; x < waveCollapse->getChunkSize(); x++) {
        for (int y = 0; y < waveCollapse->getChunkSize(); y++) {

            Color color = WHITE;
            if ((1 - chunk->getTile(x, y)->state.at(0))  < .001) {color = BLUE;}
            if ((1 - chunk->getTile(x, y)->state.at(1))  < .001) {color = BROWN;}

            DrawRectangle(x*50, y*50, 50, 50, color);
        }
    }

}