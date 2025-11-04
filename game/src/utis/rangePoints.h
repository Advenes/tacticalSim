#pragma once
#include <vector>
#include <iostream>
#include "events/orders/orders.h"
#include "raylib.h"

#ifndef FOREST_POINT
#define FOREST_POINT 60
#endif

#ifndef CITY_POINT
#define CITY_POINT 70
#endif

#ifndef FIELD_POINT
#define FIELD_POINT 10
#endif

#ifndef FOREST_COLOR
#define FOREST_COLOR
const Color FOREST = {9, 105, 33, 255};
#endif

#ifndef FIELD_COLOR
#define FIELD_COLOR
const Color FIELD  = {219, 215, 0, 255};
#endif

#ifndef CITY_COLOR
#define CITY_COLOR
const Color CITY   = {192, 122, 0, 255};
#endif

#ifndef COLOR_EQ_OPERATOR
#define COLOR_EQ_OPERATOR
inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
#endif


inline std::vector<MovePoint> getLinePoints(int startX, int startY, int endX, int endY, int step = 5) {
    std::vector<MovePoint> linePoints;

    int deltaX = std::abs(endX - startX);
    int deltaY = std::abs(endY - startY);
    int stepX = (startX < endX) ? step : -step;
    int stepY = (startY < endY) ? step : -step;

    int error = deltaX - deltaY;
    int currentX = startX;
    int currentY = startY;

    while (true) {
        linePoints.push_back({currentX, currentY});
        std::cout << "point: " << currentX << ", " << currentY << '\n';

        // Stop if we're close enough to the destination
        if (std::abs(currentX - endX) <= step && std::abs(currentY - endY) <= step)
            break;

        int doubleError = 2 * error;

        if (doubleError > -deltaY) {
            error -= deltaY;
            currentX += stepX;
        }
        if (doubleError < deltaX) {
            error += deltaX;
            currentY += stepY;
        }
    }

    return linePoints;
}

inline bool checkForHeightObstructions(Vector2 first, Vector2 second, std::vector<MovePoint> points) {
    Image* heightImg = TextureManager::get().getImage("mapHeight");
    if (!heightImg) {
        std::cout << "Heightmap not loaded!\n";
        return false;
    }

    auto getHeight = [&](float x, float y) -> int {
        Color c = GetImageColor(*heightImg, (int)x, (int)y);
        return c.r;
    };

    int h1 = getHeight(first.x, first.y);
    int h2 = getHeight(second.x, second.y);
    int margin = 8;

    for (size_t i = 0; i < points.size(); i++) {
        float t = (float)i / (points.size() - 1);
        float expectedHeight = h1 + t * (h2 - h1);
        int actualHeight = getHeight(points[i].x, points[i].y);

        if (actualHeight > expectedHeight + margin) {
            std::cout << "OBSTRUCTION at (" << points[i].x << ", " << points[i].y << ") "
                      << "actual=" << actualHeight
                      << " expected=" << expectedHeight << std::endl;
            return true;
        }
    }

    return false;
}

inline bool checkForTerrainObstructions(Vector2 FirstUnitPos, Vector2 SecondUnitPos, std::vector<MovePoint> points, int effectiveRange){
    Image* terrainImg = TextureManager::get().getImage("mapTerrain");
    Color firstPosColor = GetImageColor(*terrainImg, FirstUnitPos.x, FirstUnitPos.y);

    int terrainPoints = 0;

    for(auto& [pointX, pointY] : points){
        Color color = GetImageColor(*terrainImg, pointX, pointY);
        if(color == CITY){
            if(firstPosColor == CITY) {terrainPoints += CITY_POINT / 2; continue;};
            terrainPoints += CITY_POINT;
        }
        else if(color == FIELD){
            if(firstPosColor == FIELD) {terrainPoints += FIELD_POINT / 2; continue;};
            terrainPoints += FIELD_POINT;
        }
        else if (color == FOREST){
            if(firstPosColor == FOREST) {terrainPoints += FOREST_POINT / 2; continue;};
            terrainPoints += FOREST_POINT;
        }
    }



    if(terrainPoints > effectiveRange){
        return true;
    }
    return false;
}