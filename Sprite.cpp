#include "Sprite.h"
#include "defs.h"
#include "Player.h"
#include "Graphics.h"
#include "Texture.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::update(float deltaTime)
{
}

void Sprite::render()
{
	auto player = Player::get();
	auto g = Graphics::get();

	float perpDistance = distance * cos(angle);

	float spriteHeight = TILE_SIZE / perpDistance * DIST_PROJ_PLANE;
	float spriteWidth = spriteHeight;

	float spriteTopY = (g->getScreenHeight() / 2) - (spriteHeight / 2);
	spriteTopY = spriteTopY < 0 ? 0 : spriteTopY;

	float spriteBottomY = (g->getScreenHeight() / 2) + spriteHeight / 2;
	spriteBottomY = spriteBottomY > g->getScreenHeight() ? g->getScreenHeight() : spriteBottomY;

	float spriteAngle = atan2(y - player->y, x - player->x) - player->rotationAngle;
	float spriteScreenPosX = tan(spriteAngle) * DIST_PROJ_PLANE;

	float spriteLeftX = (g->getScreenWidth() / 2) + spriteScreenPosX - spriteWidth / 2;
	float spriteRightX = spriteLeftX + spriteWidth;

	int textureWidth = texture->getTextureWidth();
	int textureHeight = texture->getTextureHeight();

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

				uint32_t texelColor = texture->getValueAt(textureOffsetX, textureOffsetY);

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
