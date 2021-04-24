#include "SpriteManager.h"
#include "Sprite.h"
#include "TextureLoader.h"
#include "Player.h"
#include "Texture.h"
#include "defs.h"
#include "Utils.h"

static SpriteManager* spriteManager = nullptr;
static std::vector<Sprite*> sprites;

SpriteManager::SpriteManager()
{
	auto table = new Sprite();
	table->x = 500;
	table->y = 800;
	table->texture = TextureLoader::get()->getSpriteTexture("table");

	auto light = new Sprite();
	light->x = 500;
	light->y = 800;
	light->texture = TextureLoader::get()->getSpriteTexture("light");

	auto armor = new Sprite();
	armor->x = TILE_SIZE * 1.5f;
	armor->y = TILE_SIZE * 1.5f;
	armor->texture = TextureLoader::get()->getSpriteTexture("armor");

	auto armor2 = new Sprite();
	armor2->x = MAP_NUM_COLS * TILE_SIZE - TILE_SIZE * 1.5f;
	armor2->y = TILE_SIZE * 1.5f;
	armor2->texture = TextureLoader::get()->getSpriteTexture("armor");

	auto barrel = new Sprite();
	barrel->x = TILE_SIZE * 4;
	barrel->y = 800;
	barrel->texture = TextureLoader::get()->getSpriteTexture("barrel");

	auto barrel2 = new Sprite();
	barrel2->x = MAP_NUM_COLS * TILE_SIZE - TILE_SIZE * 4;
	barrel2->y = 800;
	barrel2->texture = TextureLoader::get()->getSpriteTexture("barrel");

	sprites.push_back(table);
	sprites.push_back(light);
	sprites.push_back(armor);
	sprites.push_back(armor2);
	sprites.push_back(barrel);
	sprites.push_back(barrel2);
}


SpriteManager::~SpriteManager()
{
	for (auto sprite : sprites)
		delete sprite;

	sprites.clear();
}

SpriteManager* SpriteManager::get()
{
	if (!spriteManager)
		spriteManager = new SpriteManager();

	return spriteManager;
}

void SpriteManager::getVisibleSprites(std::vector<Sprite*>& visibleSprites)
{
	visibleSprites.clear();

	auto player = Player::get();

	for (int i = 0; i < sprites.size(); i++)
	{
		float angleSpritePlayer = player->rotationAngle - atan2(sprites[i]->y - player->y, sprites[i]->x - player->x);

		if (angleSpritePlayer > M_PI)
			angleSpritePlayer -= 2 * M_PI;

		if (angleSpritePlayer < -M_PI)
			angleSpritePlayer += 2 * M_PI;

		angleSpritePlayer = fabs(angleSpritePlayer);

		const float EPSILON = 0.2;
		if (angleSpritePlayer < FOV_ANGLE / 2 + EPSILON)
		{
			sprites[i]->visible = true;
			sprites[i]->angle = angleSpritePlayer;
			sprites[i]->distance = distanceBetweenPoints(sprites[i]->x, sprites[i]->y, player->x, player->y);
			visibleSprites.push_back(sprites[i]);
		}
		else
			sprites[i]->visible = false;
	}
}

void SpriteManager::getAllSprites(std::vector<Sprite*>& allSprites)
{
	auto temp = sprites;
	allSprites = temp;
}

void SpriteManager::renderSprites()
{
	std::vector<Sprite*> visibleSprites;
	getVisibleSprites(visibleSprites);

	// sort visible sprites
	for (int i = 0; i < (int)visibleSprites.size() - 1; i++)
		for (int j = i + 1; j < (int)visibleSprites.size(); j++)
		{
			if (visibleSprites[j]->distance > visibleSprites[i]->distance)
			{
				auto temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}

	for (auto sprite : visibleSprites)
		sprite->render();
}
