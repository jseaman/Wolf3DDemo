#pragma once

class Texture;

class TextureLoader
{
	public:
		~TextureLoader();

		static TextureLoader* get();

		Texture* getTexture(const char* textureName);
		Texture* getTexture(int index);

	private:
		TextureLoader();
		
		void loadAllTextures();
};

