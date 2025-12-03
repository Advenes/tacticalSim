#pragma once
#include <iostream>

#include "camera/camera.h"
#include "render/render.h"
#include "inputs/inputHandler.h"
#include "inputs/inputState.h"
#include "events/eventHandler.h"
#include "scene/scene.h"
#include "interface/interface.h"
#include "time/time.h"

static constexpr int InitalWidth = 1200;
static constexpr int InitalHeight = 800;

class Game{
public:
	Game() : scene(&entityHandler), inputHandler(scene.getCamera(), &eventHandler), eventHandler(&entityHandler) {
        startGame();
	}
    
    ~Game(){
        endGame();
    }
    
private:
    void startGame();
    
    void gameLoop();
    
    void endGame();
    
private:
    Interface interface;
    EntityHandler entityHandler;
    Scene scene;
    EventHandler eventHandler;
    InputHandler inputHandler;
};
