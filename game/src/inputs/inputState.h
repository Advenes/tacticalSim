#pragma once
#include "entities/entity.h"

struct InputState {
    bool selecting = false;
    bool timeKeyPressed = false;
    Position selPos;
};
