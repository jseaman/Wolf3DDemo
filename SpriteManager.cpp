#include "SpriteManager.h"
#include "Sprite.h"
#include "TextureLoader.h"
#include "Player.h"
#include "Graphics.h"
#include "Texture.h"
#include "defs.h"
#include "Utils.h"

static SpriteManager* spriteManager = nullptr;
static std::vector<Sprite*> sprites;

SpriteManager::SpriteManager()
{
	auto barrel = new Sprite();
	barrel->x = 500;
	barrel->y = 800;
	barrel->texture = TextureLoader::get()->getSpriteTexture("barrel");

	sprites.push_back(barrel);
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

	auto g = Graphics::get();
	auto player = Player::get();

	for (auto sprite : visibleSprites)
	{
		float perpDistance = sprite->distance * cos(sprite->angle);

		float spriteHeight = TILE_SIZE / perpDistance * DIST_PROJ_PLANE;
		float spriteWidth = spriteHeight;

		float spriteTopY = (g->getScreenHeight() / 2) - (spriteHeight / 2);
		spriteTopY = spriteTopY < 0 ? 0 : spriteTopY;

		float spriteBottomY = (g->getScreenHeight() / 2) + spriteHeight / 2;
		spriteBottomY = spriteBottomY > g->getScreenHeight() ? g->getScreenHeight() : spriteBottomY;

		float spriteAngle = atan2(sprite->y - player->y, sprite->x - player->x) - player->rotationAngle;
		float spriteScreenPosX = tan(spriteAngle) * DIST_PROJ_PLANE;

		float spriteLeftX = (g->getScreenWidth() / 2) + spriteScreenPosX - spriteWidth / 2;
		float spriteRightX = spriteLeftX + spriteWidth;

		int textureWidth = sprite->texture->getTextureWidth(); 
		int textureHeight = sprite->texture->getTextureHeight(); 

		for (int y = spriteTopY; y < spriteBottomY; y++)
		{
			for (int x = spriteLeftX; x < spriteRightX; x++)
			{
				float texelWidth = textureWidth / spriteWidth;
				int textureOffsetX = (x - spriteLeftX) * texelWidth;

				if (x > 0 && x < g->getScreenWidth() && y>0 && y < g->getScreenHeight())
				{
					int distanceFromTop = y + spriteHeight / 2 - g->getScreenHeight() / 2;
					int textureOffsetY = distanceFromTop * textureHeight / spriteHeight;

					uint32_t texelColor = sprite->texture->getValueAt(textureOffsetX, textureOffsetY);

					// TODO: occlude

					if (texelColor != 0xffff00ff)
					{
						g->setDrawingColor(texelColor);
						g->drawPixel(x, y);
					}
				}
			}
		}
	}
}
