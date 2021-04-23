#pragma once
#include "DrawableObject.h"

class MiniMap :
    public DrawableObject
{
    public:
        static MiniMap* get();

        virtual void update(float deltaTime) override;
        virtual void render() override;

        bool hasWallAt(float x, float y);
        int getMapValueAt(float x, float y);

    protected:
        void renderMiniMap();
        void renderMiniMapRays();
        void renderMiniMapSprites();

    private:
        MiniMap();
};

