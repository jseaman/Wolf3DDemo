#include "Graphics.h"
#include <iostream>
#include <exception>
#include <SDL.h>
#undef main


static Graphics* graphics;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

Graphics::Graphics()
{
    initializeSDL();
}

Graphics* Graphics::get()
{
    if (!graphics)
        graphics = new Graphics();

    return graphics;
}

void Graphics::setDrawingColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Graphics::drawRectangle(int x, int y, int w, int h)
{
    SDL_Rect rect = { x,y,w,h };
    SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::drawFilledRectangle(int x, int y, int w, int h)
{
    SDL_Rect rect = { x,y,w,h };
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::render()
{
    SDL_RenderPresent(renderer);
}

int Graphics::getScreenWidth()
{
    return fullScreenWidth;
}

int Graphics::getScreenHeight()
{
    return fullScreenHeight;
}

void Graphics::initializeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::logic_error("Error initializing SDL");
        
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
        throw std::logic_error("Error creating SDL window");
        
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
        throw std::logic_error("Error creating SDL renderer");
}

Graphics::~Graphics()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);
    
    SDL_Quit();
}


