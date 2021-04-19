#include "Player.h"
#include "defs.h"
#include <SDL.h>
#include "Graphics.h"
#include "Player.h"
#include <math.h>
#include "MiniMap.h"
#include "Utils.h"

static Player* player = nullptr;

Player::Player()
{
    x = TILE_SIZE * MAP_NUM_COLS / 2.0f;
    y = TILE_SIZE * MAP_NUM_ROWS / 2.0f;

    turnDirection = 0;
    walkDirection = 0;
    rotationAngle = M_PI / 2;
    walkSpeed = 150;
    turnSpeed = 65 * M_PI / 180;
}

void Player::update(float deltaTime)
{
    rotationAngle += turnDirection * turnSpeed * deltaTime;
    normalizeAngle(&rotationAngle);

    float moveStep = walkDirection * walkSpeed * deltaTime;

    float newPlayerX = x + cos(rotationAngle) * moveStep;
    float newPlayerY = y + sin(rotationAngle) * moveStep;

    if (!MiniMap::get()->hasWallAt(newPlayerX, newPlayerY))
    {
        x = newPlayerX;
        y = newPlayerY;
    }
}

void Player::render()
{
    auto g = Graphics::get();
    auto player = Player::get();

    g->setDrawingColor(0, 255, 0, 255);
    
    g->drawLine(
        player->x * MINIMAP_SCALE,
        player->y * MINIMAP_SCALE,
        round(player->x + 40 * cos(player->rotationAngle)) * MINIMAP_SCALE,
        round(player->y + 40 * sin(player->rotationAngle)) * MINIMAP_SCALE
    );

    g->drawFilledRectangle(
        (player->x - 2) * MINIMAP_SCALE,
        (player->y - 2) * MINIMAP_SCALE,
        5 * MINIMAP_SCALE,
        5 * MINIMAP_SCALE);
}

Player* Player::get()
{
	if (!player)
		player = new Player();

	return player;
}

Player::~Player()
{

}
