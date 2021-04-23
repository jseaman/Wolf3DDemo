#pragma once
#include <vector>

class Sprite;


class SpriteManager
{
	public:
		~SpriteManager();

		static SpriteManager* get();

		void getVisibleSprites(std::vector<Sprite*>& visibleSprites);
		void getAllSprites(std::vector<Sprite*>& sprites);

		void renderSprites();

	private:
		SpriteManager();
};

