#include "Graphics.h"
#include <iostream>
#include <exception>
#include "defs.h"
#include <SDL.h>
#undef main


static Graphics* graphics;
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static uint32_t* colorBuffer = NULL;
static SDL_Texture* colorBufferTexture;

static uint32_t drawingColor;

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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    colorBuffer = new uint32_t[RESOLUTION_WIDTH * RESOLUTION_HEIGHT];

    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        RESOLUTION_WIDTH,
        RESOLUTION_HEIGHT
    );
}

void Graphics::setDrawingColor(int r, int g, int b, int a)
{
    drawingColor = a;
    drawingColor <<= 8;
    drawingColor |= b;
    drawingColor <<= 8;
    drawingColor |= g;
    drawingColor <<= 8;
    drawingColor |= r;
}

void Graphics::setDrawingColor(uint32_t color)
{
    drawingColor = color;
}

void Graphics::drawPixel(int x, int y)
{
    if (x < 0 || x >= RESOLUTION_WIDTH || y < 0 || y >= RESOLUTION_HEIGHT)
        return;

    colorBuffer[y * RESOLUTION_WIDTH + x] = drawingColor;
}

void Graphics::drawRectangle(int x, int y, int w, int h)
{
    drawLine(x, y, x + w, y);
    drawLine(x, y + h, x + w, y + h);
    
    drawLine(x, y, x, y + h);
    drawLine(x + w, y, x + w, y + h);
}

void Graphics::drawFilledRectangle(int x, int y, int w, int h)
{
    if (x < 0)
    {
        w += x;
        x = 0;
    }
    else if (x >= RESOLUTION_WIDTH)
    {
        w -= RESOLUTION_WIDTH - x;
        x = RESOLUTION_WIDTH - 1;
    }

    if (y < 0)
    {
        h += y;
        y = 0;
    }
    else if (y >= RESOLUTION_HEIGHT)
    {
        h -= RESOLUTION_HEIGHT - y;
        y = RESOLUTION_HEIGHT - 1;
    }

    if (x + w >= RESOLUTION_WIDTH)
        w = RESOLUTION_WIDTH - x;

    if (y + h > RESOLUTION_HEIGHT)
        h = RESOLUTION_HEIGHT - y;
    
    for (int y_iter = y; y_iter <= y + h; y_iter++)
        for (int x_iter = x; x_iter <= x + w; x_iter++)
            drawPixel(x_iter, y_iter);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    int longestSide = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)longestSide;
    float yIncrement = deltaY / (float)longestSide;

    float currentX = x1;
    float currentY = y1;

    for (int i = 0; i < longestSide; i++)
    {
        drawPixel(round(currentX), round(currentY));
        currentX += xIncrement;
        currentY += yIncrement;
    }
}

void Graphics::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    memset(colorBuffer, 0, RESOLUTION_WIDTH * RESOLUTION_HEIGHT * sizeof(uint32_t));
}

void Graphics::render()
{
    SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer, (int)(RESOLUTION_WIDTH * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

const int Graphics::getScreenWidth()
{
    return RESOLUTION_WIDTH;
}

const int Graphics::getScreenHeight()
{
    return RESOLUTION_HEIGHT;
}

Graphics::~Graphics()
{
    delete[] colorBuffer;
    SDL_DestroyTexture(colorBufferTexture);

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);
    
    SDL_Quit();
}




