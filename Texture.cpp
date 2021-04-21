#include "Texture.h"
#include <iostream>
#include <exception>

Texture::Texture(const char* fileName)
{
    upng_t* upng = nullptr;

    upng = upng_new_from_file(fileName);

    if (upng) 
    {
        upng_decode(upng);

        if (upng_get_error(upng) == UPNG_EOK)
        {
            textureWidth = upng_get_width(upng);
            textureHeight = upng_get_height(upng);
            textureBuffer = (uint32_t*)upng_get_buffer(upng);
            upngTexture = upng;
        }
        else
        {
            textureBuffer = nullptr;
            upngTexture = nullptr;
            throw std::logic_error(std::string("Error decoding texture <") + fileName + ">");
        }
    }
    else
        throw std::logic_error(std::string("Error loading texture <") + fileName + ">");
}

Texture::~Texture()
{
    upng_free(upngTexture);
}

const int Texture::getTextureWidth()
{
    return textureWidth;
}

const int Texture::getTextureHeight()
{
    return textureHeight;
}

const uint32_t Texture::getValueAt(int x, int y)
{
    int index = y * textureWidth + x;

    if (index >= textureWidth * textureHeight)
        throw std::logic_error("Texture buffer out of bounds");

    return textureBuffer[index];
}
