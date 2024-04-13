#include <iostream>
#include "raylib-cpp.hpp"
#include <cstdlib>
#include "WaveCollapse.h"
#include "Chunk.h"
#include <chrono>

void update();
void render();

Vector2 mousePos;
Vector2 screenDimensions = {1000, 1000};
Vector2 cameraPos = {0, 0};


bool debug = false;

#define WIDTH 5
#define CHUNKWIDTH (WIDTH * 15)

std::vector<Constraint> constraints;
WaveCollapse* waveCollapse;

typedef enum {NORTH, EAST, WEST, SOUTH} direction_t;
typedef enum {SPRING, SUMMER, FALL, WINTER} season_t;

bool compare(int x) {
    return x == WINTER;
}


int main() {

    direction_t test = NORTH;

    bool x = compare(WEST);

    std::cout << x << std::endl;


    constraints.emplace_back( Constraint{CORD, 1, 0, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 0, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 1, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 1, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 2, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 2, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 2, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 1, 2, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 0, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 0, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 1, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 1, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 2, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 2, {-1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 2, {1, 0}});
    constraints.emplace_back( Constraint{CORD, 3, 2, {-1, 0}});

    /*
    constraints.emplace_back( Constraint{CORD, 1, 0, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 1, 0, {0, -1}});
    constraints.emplace_back( Constraint{CORD, 1, 1, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 1, 1, {0, -1}});
    constraints.emplace_back( Constraint{CORD, 1, 3, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 1, 3, {0, -1}});

    constraints.emplace_back( Constraint{CORD, 2, 0, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 2, 0, {0, -1}});
    constraints.emplace_back( Constraint{CORD, 2, 1, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 2, 1, {0, -1}});
    constraints.emplace_back( Constraint{CORD, 2, 3, {0, 1}});
    constraints.emplace_back( Constraint{CORD, 2, 3, {0, -1}});




    //constraints.emplace_back( Constraint{CORD, 1, 1, {1, 0}});
    //constraints.emplace_back( Constraint{CORD, 1, 1, {-1, 0}});

*/


    waveCollapse = new WaveCollapse(std::vector<float>{.898, .1, .001, .001} ,constraints,15);
    const auto p1 = std::chrono::system_clock::now();
    waveCollapse->setSeed(std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count());

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
    if (IsKeyDown(KEY_LEFT)) {
        cameraPos.x -= 5;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        cameraPos.x += 5;
    }
    if (IsKeyDown(KEY_UP)) {
        cameraPos.y -= 5;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        cameraPos.y += 5;
    }

    for (int x = -1; x < (screenDimensions.x / CHUNKWIDTH + 1); x++) {
        int x2 = x + cameraPos.x / CHUNKWIDTH;
        for (int y = -1; y < (screenDimensions.y / CHUNKWIDTH + 1); y++) {
            int y2 = y + cameraPos.y / CHUNKWIDTH;

            if (!waveCollapse->containsChunk(x2, y2)) {
                waveCollapse->GenerateChunk(x2, y2);
            }
        }
    }
}

void render() {

    DrawCircle(mousePos.x, mousePos.y, 5, RED);

    for (int chunkX = -1; chunkX < (screenDimensions.x / CHUNKWIDTH + 1); chunkX++) {
        int chunkX2 = chunkX + cameraPos.x / CHUNKWIDTH;

        for (int chunkY = -1; chunkY < (screenDimensions.y / CHUNKWIDTH + 1); chunkY++) {
            int chunkY2 = chunkY + cameraPos.y / CHUNKWIDTH;

            Chunk* chunk = waveCollapse->getChunk(chunkX2, chunkY2);

            for (int x = 0; x < waveCollapse->getChunkSize(); x++) {
                for (int y = 0; y < waveCollapse->getChunkSize(); y++) {

                    Tile* tile = chunk->getTile(x, y);

                    //if (chunkX*WIDTH+cameraPos.chunkX > 0 && chunkX*WIDTH+cameraPos.chunkX < screenDimensions.chunkX &&
                    //    chunkY*WIDTH+cameraPos.chunkY > 0 && chunkY*WIDTH+cameraPos.chunkY < screenDimensions.chunkY) {
                        Color color = WHITE;
                        if ((1 - tile->state.at(0)) < .001) { color = BLUE; }
                        if ((1 - tile->state.at(1)) < .001) { color = BROWN; }
                        if ((1 - tile->state.at(2)) < .001) { color = GREEN; }

                        DrawRectangle(chunkX2 * CHUNKWIDTH + x * WIDTH - cameraPos.x,
                                      chunkY2 * CHUNKWIDTH + y * WIDTH - cameraPos.y,
                                      WIDTH, WIDTH, color);
                    //}
                }
            }
        }
    }


}