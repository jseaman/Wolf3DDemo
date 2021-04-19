#pragma once

#include "DrawableObject.h"
#include "Ray.h"
#include <vector>

class RayCaster 
	:public DrawableObject
{
	public:
		~RayCaster();

		static RayCaster* get();

		void castAllRays();

		virtual void update(float deltaTime) override;
		virtual void render() override;

	protected:
		void castRay(float rayAngle, int stripId);
		bool isInsideMap(float x, float y);

	private:
		RayCaster();
		std::vector<Ray> rays;
};

