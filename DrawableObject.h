#pragma once
class DrawableObject 
{
	public:
		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;
};

