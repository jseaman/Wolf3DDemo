#pragma once
#include "DrawableObject.h"
class MiniMap :
    public DrawableObject
{
    public:
        virtual void update(float deltaTime) override;
        virtual void render() override;
};

