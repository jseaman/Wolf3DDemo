#include "Utils.h"
#include <math.h>
#include <SDL_stdinc.h>

void normalizeAngle(float &angle)
{
	angle = remainder(angle, 2 * M_PI);

	if (angle < 0)
		angle = 2 * M_PI + angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void changeColorIntensity(uint32_t& color, float factor)
{
	uint32_t a = color & 0xff000000;
	uint32_t b = (color & 0x00ff0000) * factor;
	uint32_t g = (color & 0x0000ff00) * factor;
	uint32_t r = (color & 0x000000ff) * factor;

	color = a | (b & 0x00ff0000) | (g & 0x0000ff00) | (r & 0x000000ff);
}
