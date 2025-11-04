#pragma once
#include "entities/entity.h"

struct InputState {
    bool selecting = false;
    bool timeKeyPressed = false;
    bool measuring = false;
    Position selPos;
    Vector2 measPos;
    double measuringDistance = 0;
};
