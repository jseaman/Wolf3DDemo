#include "RayCaster.h"
#include "Graphics.h"
#include "Player.h"
#include "MiniMap.h"
#include "defs.h"
#include "Utils.h"

static RayCaster* rayCaster = nullptr;

RayCaster::RayCaster()
{
	int numRays = Graphics::get()->getScreenWidth() / STRIP_LENGTH;

	for (int i = 0; i < numRays; i++)
		rays.push_back(Ray());
}

RayCaster::~RayCaster()
{
	rays.clear();
}

RayCaster* RayCaster::get()
{
	if (!rayCaster)
		rayCaster = new RayCaster();

	return rayCaster;
}

void RayCaster::castAllRays()
{
	float rayAngle = Player::get()->rotationAngle - FOV_ANGLE / 2;

	for (int i = 0; i < rays.size(); i++)
	{
		castRay(rayAngle, i);
		rayAngle += FOV_ANGLE / rays.size();		
	}
}

void RayCaster::castRay(float rayAngle, int stripId)
{
	normalizeAngle(&rayAngle);
	rays[stripId].rayAngle = rayAngle;

	float xintercept, yintercept;
	float xstep, ystep;

	//////////////////////////////////////////
	// Horizontal Ray-grid intersection code
	//////////////////////////////////////////

	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	yintercept = floor(Player::get()->y / TILE_SIZE) * TILE_SIZE;
	yintercept += rays[stripId].isRayFacingDown() ? TILE_SIZE : 0;

	xintercept = Player::get()->x + (yintercept - Player::get()->y) / tan(rayAngle);

	// calculate increments
	ystep = TILE_SIZE;
	ystep *= rays[stripId].isRayFacingUp() ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (rays[stripId].isRayFacingLeft() && xstep > 0) ? -1 : 1;
	xstep *= (rays[stripId].isRayFacingRight() && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (rays[stripId].isRayFacingUp() ? -1 : 0);

		if (MiniMap::get()->hasWallAt(xToCheck, yToCheck))
		{
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;

			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	//////////////////////////////////////////
	// Vertical Ray-grid intersection code
	//////////////////////////////////////////

	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	xintercept = floor(Player::get()->x  / TILE_SIZE) * TILE_SIZE;
	xintercept += rays[stripId].isRayFacingRight() ? TILE_SIZE : 0;

	yintercept = Player::get()->y + (xintercept - Player::get()->x) * tan(rayAngle);

	// calculate increments
	xstep = TILE_SIZE;
	xstep *= rays[stripId].isRayFacingLeft() ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (rays[stripId].isRayFacingUp() && ystep > 0) ? -1 : 1;
	ystep *= (rays[stripId].isRayFacingDown() && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// Increment xstep and ystep until we find a wall

	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		float xToCheck = nextVertTouchX + (rays[stripId].isRayFacingLeft() ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (MiniMap::get()->hasWallAt(xToCheck, yToCheck))
		{
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;

			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}


	// calculate both horizontal and vertical distances, choose smallest value
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(Player::get()->x, Player::get()->y, horzWallHitX, horzWallHitY)
		: FLT_MAX;

	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(Player::get()->x, Player::get()->y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (horzHitDistance < vertHitDistance)
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wasHitVertical = false;
	}
	else
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wasHitVertical = true;
	}

	rays[stripId].rayAngle = rayAngle;
}

bool RayCaster::isInsideMap(float x, float y)
{
	return x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE;
}

void RayCaster::update(float deltaTime)
{
	castAllRays();
}

void RayCaster::render()
{
	auto player = Player::get();

	Graphics::get()->setDrawingColor(255, 255, 0, 128);

	for (int i = 0; i < rays.size(); i += 50)
		Graphics::get()->drawLine(player->x, player->y, rays[i].wallHitX, rays[i].wallHitY);
}


