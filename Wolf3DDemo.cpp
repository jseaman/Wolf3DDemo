// Wolf3DDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdbool.h>

#include <SDL.h>
#undef main

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

bool isGameRunning = true;

int fullScreenWidth;
int fullScreenHeight;

#define TILE_SIZE 64

#define MAP_NUM_ROWS 15
#define MAP_NUM_COLS 16

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct
{
    float x;
    float y;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;

player_t player;

bool initializeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    fullScreenWidth = displayMode.w;
    fullScreenHeight = displayMode.h;

    window = SDL_CreateWindow(
        "Wolf3D Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        fullScreenWidth,
        fullScreenHeight,
        SDL_WINDOW_OPENGL
    );

    if (!window)
    {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer" << std::endl;
    }

    return true;
}

bool setup()
{
    if (!initializeSDL())
        return false;

    player.x = TILE_SIZE * MAP_NUM_COLS / 2.0f;
    player.y = TILE_SIZE * MAP_NUM_ROWS / 2.0f;

    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = M_PI/2;
    player.walkSpeed = 150;
    player.turnSpeed = 45 * M_PI / 180;

    return true;
}

void processInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            isGameRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isGameRunning = false;

            break;
    }
}

void update()
{

}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    SDL_Rect rect;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    for (int i = 0; i < MAP_NUM_ROWS; i++)
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            rect.x = j * TILE_SIZE;
            rect.y = i * TILE_SIZE; 

            if (map[i][j] == 0)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            else 
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_RenderFillRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    rect.x = player.x-2;
    rect.y = player.y-2;
    rect.w = 5;
    rect.h = 5;

    SDL_RenderDrawLine(renderer, player.x, player.y, player.x + 40 * cos(player.rotationAngle), player.y + 40 * sin(player.rotationAngle));

    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void releaseResources()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main()
{
    if (!setup())
        return 1;

    while (isGameRunning)
    {
        processInput();
        update();
        render();
    }

    releaseResources();

    return 0;
}

