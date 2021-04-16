#include "Player.h"
#include "defs.h"
#include <SDL.h>
#include "Graphics.h"
#include "Player.h"
#include <math.h>

static Player* player = nullptr;

Player::Player()
{
    x = TILE_SIZE * MAP_NUM_COLS / 2.0f;
    y = TILE_SIZE * MAP_NUM_ROWS / 2.0f;

    turnDirection = 0;
    walkDirection = 0;
    rotationAngle = M_PI / 2;
    walkSpeed = 150;
    turnSpeed = 45 * M_PI / 180;
}

void Player::update(float deltaTime)
{
}

void Player::render()
{
    auto g = Graphics::get();
    auto player = Player::get();

    g->setDrawingColor(0, 255, 0, 255);
    
    g->drawLine(
        player->x, 
        player->y, 
        round(player->x + 40 * cos(player->rotationAngle)), 
        round(player->y + 40 * sin(player->rotationAngle)));

    g->drawFilledRectangle(player->x - 2, player->y - 2, 5, 5);
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
