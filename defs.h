#pragma once

#include <SDL_stdinc.h>
#include <math.h>

#define TILE_SIZE 64

#define MAP_NUM_ROWS 15
#define MAP_NUM_COLS 16

#define FPS 30
#define FRAME_TIME_LENGTH (1000.0f / FPS)

#define FOV_ANGLE (60 * M_PI / 180)

#define MINIMAP_SCALE 0.10f

#define RESOLUTION_WIDTH 800
#define RESOLUTION_HEIGHT 600

static const float DIST_PROJ_PLANE = ((RESOLUTION_WIDTH / 2) / tan(FOV_ANGLE / 2));