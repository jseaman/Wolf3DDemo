#pragma once

#include <SDL_stdinc.h>

#define TILE_SIZE 64

#define MAP_NUM_ROWS 15
#define MAP_NUM_COLS 16

#define FPS 30
#define FRAME_TIME_LENGTH (1000.0f / FPS)

#define FOV_ANGLE (60 * M_PI / 180)

#define STRIP_LENGTH 10

#define MINIMAP_SCALE 0.15f

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 800