#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "entity.h"
#include "render.h"
#include "inputState.h"
#include "eventHandler.h"

class InputHandler {
public:
	InputState inputState;

	void inputReciever(Camera2D* cam, Render* render);
	void mouseInput(EntityHandler* entityHandler, Camera2D* camera, EventHandler* eventHandler);
};

