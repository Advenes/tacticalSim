#include "render.h"

void Render::renderSprite(Texture2D *texture, Vector2 position, float scale, Color color){
    DrawTextureEx(*texture, position, 0.0f, scale, color);
}
