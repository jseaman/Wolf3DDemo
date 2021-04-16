#include "MiniMap.h"
#include "defs.h"
#include "Graphics.h"
#include <math.h>

static MiniMap* miniMap = nullptr;

static int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

MiniMap::MiniMap()
{

}

MiniMap* MiniMap::get()
{
    if (!miniMap)
        miniMap = new MiniMap();

    return miniMap;
}

void MiniMap::update(float deltaTime)
{
}

void MiniMap::render()
{
    auto g = Graphics::get();

    for (int i = 0; i < MAP_NUM_ROWS; i++)
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            if (map[i][j] == 0)
                g->setDrawingColor(0, 0, 0, 255);
            else
                g->setDrawingColor(255, 255, 255, 255);

            g->drawFilledRectangle(x, y, TILE_SIZE, TILE_SIZE);

            g->setDrawingColor(128, 0, 0, 255);
            g->drawRectangle(x, y, TILE_SIZE, TILE_SIZE);
        }
}

bool MiniMap::hasWallAt(float x, float y)
{
    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
        return true;

    int i = floor(y / TILE_SIZE);
    int j = floor(x / TILE_SIZE);

    return map[i][j] != 0;
}
