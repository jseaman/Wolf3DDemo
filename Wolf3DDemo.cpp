// Wolf3DDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdbool.h>
#include "Graphics.h"
#include "MiniMap.h"
#include "Player.h"
#include <SDL.h>
#undef main

bool isGameRunning = true;

MiniMap* map = nullptr;

bool setup()
{
    map = new MiniMap();
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
    map->render();
    Player::get()->render();
    Graphics::get()->render();
}

void releaseResources()
{
    delete map;
    delete Player::get();
    delete Graphics::get();
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

