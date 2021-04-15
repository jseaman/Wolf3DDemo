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
    return initializeSDL();
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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;

    SDL_RenderFillRect(renderer, &rect);

    rect.x = 200;
    rect.y = 200;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

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

