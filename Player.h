#pragma once
#include "DrawableObject.h"
class Player :
    public DrawableObject
{
    public:
        static Player* get();

        float x;
        float y;
        int turnDirection;
        int walkDirection;
        float rotationAngle;
        float walkSpeed;
        float turnSpeed;

        virtual void update(float deltaTime) override;
        virtual void render() override;

        ~Player();

    private:
        Player();
};

