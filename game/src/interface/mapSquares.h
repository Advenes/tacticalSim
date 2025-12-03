#pragma once
#include <iostream>
#include <vector>
#include "render/render.h"
#include "camera/camera.h"

class RenderedSquares {
    public:
    RenderedSquares() {};

    void renderSquares(Cam* camera);

private:
    const std::vector<int> squareSizes = {1,2,5,10,15,20,40,80, 160, 250, 500};
    const int minSquares = 8;
    const int maxSquares = 18;
    const float mapScaleMultiplier = 3.35;
    std::pair<int,int> fullSquareSize = {33,33};
};
