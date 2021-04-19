#pragma once
class Ray
{
	public:
		Ray();
		~Ray();

		float rayAngle;
		float wallHitX;
		float wallHitY;
		float distance;
		bool wasHitVertical;

		bool isRayFacingUp();
		bool isRayFacingDown();
		bool isRayFacingLeft();
		bool isRayFacingRight();
};

