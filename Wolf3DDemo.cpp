// Wolf3DDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdbool.h>

bool isGameRunning = true;

void setup()
{

}

void processInput()
{

}

void update()
{

}

void render()
{
    std::cout << "Estoy jugando" << std::endl;
}

void releaseResources()
{

}

int main()
{
    setup();

    while (isGameRunning)
    {
        processInput();
        update();
        render();
    }

    releaseResources();

    return 0;
}

