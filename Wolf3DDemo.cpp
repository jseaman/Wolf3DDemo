// Wolf3DDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdbool.h>
#include "Graphics.h"
#include "MiniMap.h"
#include "Player.h"
#include "defs.h"
#include <SDL.h>
#undef main

bool isGameRunning = true;
MiniMap* map = nullptr;
uint32_t ticksLastFrame = 0;

bool setup()
{
    map = new MiniMap();
    return true;
}

void processInput()
{
    auto player = Player::get();

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
            else if (event.key.keysym.sym == SDLK_UP)
                player->walkDirection = 1;
            else if (event.key.keysym.sym == SDLK_DOWN)
                player->walkDirection = -1;
            else if (event.key.keysym.sym == SDLK_LEFT)
                player->turnDirection = -1;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                player->turnDirection = 1;

            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP)
                player->walkDirection = 0;
            else if (event.key.keysym.sym == SDLK_DOWN)
                player->walkDirection = 0;
            else if (event.key.keysym.sym == SDLK_LEFT)
                player->turnDirection = 0;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                player->turnDirection = 0;

            break;
    }
}

void update()
{
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
        SDL_Delay(timeToWait);

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    ticksLastFrame = SDL_GetTicks();

    Player::get()->update(deltaTime);
}

void render()
{
    Graphics::get()->clearScreen();
    
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

