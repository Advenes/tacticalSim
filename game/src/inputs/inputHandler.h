#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "./core/game.h"
#include "./entities/entity.h"
#include "./render/render.h"
#include "inputState.h"
#include "./events/eventHandler.h"

class InputHandler {
public:
	InputState inputState;

	void inputReciever(Camera2D* cam, Render* render);
	void mouseInput(EntityHandler* entityHandler, Camera2D* camera, EventHandler* eventHandler);
};

