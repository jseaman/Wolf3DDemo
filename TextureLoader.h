#pragma once

class Texture;
#include <map>
#include <vector>
#include <string>

class TextureLoader
{
	public:
		~TextureLoader();

		static TextureLoader* get();

		Texture* getWallTexture(const char* textureName);
		Texture* getWallTexture(int index);

		Texture* getSpriteTexture(const char* textureName);
		Texture* getSpriteTexture(int index);

	private:
		TextureLoader();
		
		void loadAllTextures(const char* directory, std::map<std::string, Texture*>& textureDict, std::vector<Texture*>& textureVect);
};

