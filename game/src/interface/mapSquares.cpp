#include "mapSquares.h"

float round2(float number) {
    float value = (int)(number * 100 + .5);
    return (float)value / 100;
}

void RenderedSquares::renderSquares(Cam* camera) {
    float zoom = camera->getZoom();
    Vector2 camTarget = { (float)camera->getTargetX(), (float)camera->getTargetY() };

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    float worldLeft   = camTarget.x;
    float worldTop    = camTarget.y;
    float worldRight  = camTarget.x + screenW / zoom;
    float worldBottom = camTarget.y + screenH / zoom;

    for (float cellSize : squareSizes) {
        float scaled = cellSize;

        if (scaled * maxSquares > (screenW / zoom)) {
            float startX = floor(worldLeft / scaled) * scaled;
            float startY = floor(worldTop  / scaled) * scaled;

            for (float x = startX; x < worldRight; x += scaled) {
                for (float y = startY; y < worldBottom; y += scaled) {
                    DrawRectangleLines(x,y,scaled,scaled,BLACK);
                    int blockSideSize = scaled * mapScaleMultiplier;
                    if (camera->getZoom() > 2.5f) continue;
                    DrawText(std::to_string(blockSideSize).c_str(),x+ (3 / camera->getZoom()), y+ (3 / camera->getZoom()), 13 / camera->getZoom(), {255,255,255,85});
                }
            }
            break;
        }
    }
}
