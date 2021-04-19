#include "Ray.h"
#include <SDL_stdinc.h>

Ray::Ray()
{
}

Ray::~Ray()
{
}

bool Ray::isRayFacingUp()
{
    return !isRayFacingDown();
}

bool Ray::isRayFacingDown()
{
    return rayAngle > 0 && rayAngle < M_PI;
}

bool Ray::isRayFacingLeft()
{
    return !isRayFacingRight();
}

bool Ray::isRayFacingRight()
{
    return rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
}
