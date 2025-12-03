#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "entities/entity.h"
#include "camera/camera.h"
#include "inputState.h"
#include "events/eventHandler.h"
#include "time/time.h"

class InputHandler {
public:
    InputHandler(Cam* _camera, EventHandler* _eventHandler){
        cam =_camera;
        eventHandler = _eventHandler;
    }

	void inputReciever();
	void mouseInput();
    InputState* getInputState(){
        return &inputState;
    };
    
private:
    Cam* cam;
    EventHandler* eventHandler;
    InputState inputState;
};

