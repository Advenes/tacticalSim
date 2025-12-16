#include "game.h"

void Game::startGame(){
    gameLoop();
}

void Game::gameLoop(){
    while (!WindowShouldClose())
    {
        inputHandler.inputReciever();
        inputHandler.mouseInput();
        GameTime::get().updateTime();
        
        // things related to time:
        if(!GameTime::get().timePaused){
            eventHandler.checkUnitStatus();
            eventHandler.executeOrders();
        }
        
        BeginDrawing();

        scene.renderScene(inputHandler.getInputState());
        
        interface.renderInterface();
        EndDrawing();
        
    }
}

void Game::endGame(){
    CloseWindow();
}
