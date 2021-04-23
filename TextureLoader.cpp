#include "TextureLoader.h"
#include "Texture.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static TextureLoader* textureLoader = nullptr;
static std::map<std::string, Texture *> textureStrDict;
static std::vector<Texture*> textures;

TextureLoader::TextureLoader()
{
	loadAllTextures();
}

void TextureLoader::loadAllTextures()
{
	for (const auto& entry : fs::directory_iterator("images"))
	{
		auto path = entry.path().generic_string();
		auto file = path.substr(path.find("/") + 1, path.size() - 1);
		auto name = file.substr(0, file.find("."));

		auto t = new Texture(path.c_str());
		textureStrDict[name] = t;
		textures.push_back(t);
	}
}

TextureLoader::~TextureLoader()
{
	for (auto texture : textures)
		delete texture;

	textures.clear();
	textureStrDict.clear();
}

TextureLoader* TextureLoader::get()
{
	if (!textureLoader)
		textureLoader = new TextureLoader();

	return textureLoader;
}

Texture* TextureLoader::getTexture(const char* textureName)
{
	return textureStrDict[textureName];
}

Texture* TextureLoader::getTexture(int index)
{
	return textures[index-1];
}
