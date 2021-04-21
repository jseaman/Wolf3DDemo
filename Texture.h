#pragma once

#include <stdint.h>

extern "C"
{
	#include "upng.h"
}

class Texture
{
	public:
		Texture(const char* fileName);
		~Texture();

		const int getTextureWidth();
		const int getTextureHeight();
		const uint32_t getValueAt(int x, int y);

	private:
		int textureWidth;
		int textureHeight;
		uint32_t* textureBuffer;
		upng_t* upngTexture;
};

