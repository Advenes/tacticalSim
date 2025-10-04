#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Render{
public:
    
    static void renderSprite(Texture2D* texture, Vector2 position, float scale, Color color);
    
private:
    Render() = delete;
};
