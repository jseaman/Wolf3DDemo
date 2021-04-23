#include "TextureLoader.h"
#include "Texture.h"
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static TextureLoader* textureLoader = nullptr;
static std::map<std::string, Texture *> wallTextureStrDict, spriteTextureStrDict;
static std::vector<Texture*> wallTextures, spriteTextures;

TextureLoader::TextureLoader()
{
	loadAllTextures("tiles", wallTextureStrDict, wallTextures);
	loadAllTextures("sprites", spriteTextureStrDict, spriteTextures);
}

void TextureLoader::loadAllTextures(const char *directory, std::map<std::string, Texture*> &textureDict, std::vector<Texture*> &textureVect)
{
	for (const auto& entry : fs::directory_iterator(directory))
	{
		auto path = entry.path().generic_string();
		auto file = path.substr(path.find("/") + 1, path.size() - 1);
		auto name = file.substr(0, file.find("."));

		auto t = new Texture(path.c_str());
		textureDict[name] = t;
		textureVect.push_back(t);
	}
}

TextureLoader::~TextureLoader()
{
	for (auto texture : wallTextures)
		delete texture;

	wallTextures.clear();
	wallTextureStrDict.clear();

	for (auto texture : spriteTextures)
		delete texture;

	spriteTextures.clear();
	wallTextureStrDict.clear();
}

TextureLoader* TextureLoader::get()
{
	if (!textureLoader)
		textureLoader = new TextureLoader();

	return textureLoader;
}

Texture* TextureLoader::getWallTexture(const char* textureName)
{
	return wallTextureStrDict[textureName];
}

Texture* TextureLoader::getWallTexture(int index)
{
	return wallTextures[index-1];
}

Texture* TextureLoader::getSpriteTexture(const char* textureName)
{
	return spriteTextureStrDict[textureName];
}

Texture* TextureLoader::getSpriteTexture(int index)
{
	return spriteTextures[index - 1];
}
