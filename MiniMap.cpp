#include "MiniMap.h"
#include "defs.h"
#include "Graphics.h"
#include "Player.h"
#include "RayCaster.h"
#include "Ray.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <vector>
#include <math.h>

static MiniMap* miniMap = nullptr;

static int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {4, 4, 6, 4, 4, 4, 7, 5, 7, 4, 4, 4, 4, 6, 4, 4},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {8, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 4},
    {8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {10, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 10},
    {10, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 10},
    {10, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 10},
    {10, 11, 10, 9, 9, 9, 3, 9, 3, 9, 9, 9, 9, 10, 12, 10},
};

static std::vector<Sprite*> sprites;

MiniMap::MiniMap()
{
    SpriteManager::get()->getAllSprites(sprites);
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

void MiniMap::renderMiniMap()
{
    auto g = Graphics::get();

    g->setDrawingColor(0, 0, 0, 255);
    g->drawFilledRectangle(
        0,
        0,
        MAP_NUM_COLS * TILE_SIZE * MINIMAP_SCALE,
        MAP_NUM_ROWS * TILE_SIZE * MINIMAP_SCALE
    );

    for (int i = 0; i < MAP_NUM_ROWS; i++)
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            if (map[i][j] == 0)
                g->setDrawingColor(0, 0, 0, 255);
            else
                g->setDrawingColor(255, 255, 255, 255);

            g->drawFilledRectangle(
                x * MINIMAP_SCALE,
                y * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE
            );

            g->setDrawingColor(128, 0, 0, 255);

            g->drawRectangle(
                x * MINIMAP_SCALE,
                y * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE
            );
        }
}

void MiniMap::renderMiniMapRays()
{
    auto player = Player::get();
    auto rays = RayCaster::get();
    auto g = Graphics::get();

    g->setDrawingColor(255, 255, 0, 128);

    for (int i = 0; i < rays->getRayNumber(); i += 50)
        g->drawLine(
            player->x * MINIMAP_SCALE,
            player->y * MINIMAP_SCALE,
            (*rays)[i].wallHitX * MINIMAP_SCALE,
            (*rays)[i].wallHitY * MINIMAP_SCALE);
}

void MiniMap::renderMiniMapSprites()
{
    auto g = Graphics::get();

    for (auto sprite : sprites)
    {
        if (sprite->visible)
            g->setDrawingColor(0, 255, 0, 255);
        else
            g->setDrawingColor(255, 0, 0, 0);

        g->drawFilledRectangle(
            sprite->x * MINIMAP_SCALE,
            sprite->y * MINIMAP_SCALE,
            2,
            2
        );
    }
}

void MiniMap::render()
{
    renderMiniMap();
    renderMiniMapRays();
    renderMiniMapSprites();
}

bool MiniMap::hasWallAt(float x, float y)
{
    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
        return true;

    int i = floor(y / TILE_SIZE);
    int j = floor(x / TILE_SIZE);

    return map[i][j] != 0;
}

int MiniMap::getMapValueAt(float x, float y)
{
    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
        return 0;

    int i = floor(y / TILE_SIZE);
    int j = floor(x / TILE_SIZE);

    return map[i][j];
}
