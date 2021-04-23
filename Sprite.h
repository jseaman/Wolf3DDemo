#pragma once

#include "DrawableObject.h"

class Texture;

class Sprite:
	public DrawableObject
{
	public:
		Sprite();
		~Sprite();

		virtual void update(float deltaTime) override;
		virtual void render() override;

		float x;
		float y;
		float distance;
		float angle;
		bool visible;
		Texture* texture;
};

