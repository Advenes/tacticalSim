#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Render{
public:
    
    static void renderSprite(Texture2D* texture, Vector2 position, float scale, Color color);
    static void renderRectangle(Vector2 position, Vector2 size, Color color);

private:
    Render() = delete;
};
