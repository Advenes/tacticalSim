#include "raylib.h"
#include "raymath.h"
#include "core/game.h"  
#include "inputs/inputHandler.h"
#include "render/render.h"
#include "entities/entity.h"
#include "events/eventHandler.h"

void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitalWidth, InitalHeight, "tacticalSim");
    SetTargetFPS(144);
    srand(time(NULL));


    // load resources
}

void GameCleanup()
{
    CloseWindow();
}

void gameLoop(Game *game, Render *render, InputHandler* input ,Camera2D *camera, EntityHandler *entityHandler, EventHandler *eventHandler) {
    render->generateMapHeightTxt();
    render->generateMapTerrainTxt();
    render->generateHudTxt();
    render->generateLoc();
    render->generatePortraits();
    render->loadFonts();

    while (!WindowShouldClose())
    {
        input->inputReciever(camera, render);
        input->mouseInput(entityHandler, camera, eventHandler);
        render->renderer(camera, entityHandler, &input->inputState);
    }

    render->unloadAll();
}


int main(){

    GameInit();

    Camera2D cam = {0};
    cam.target = { 0.0f, 0.0f };
    cam.zoom = 1.0f;

    Game game;
    Render render(&cam);
    InputHandler inputHandler;
    EntityHandler entityHandler;
    EventHandler eventHandler;
    entityHandler.addToArray(std::make_unique<Infantry>(Position(200, 300), LevelOfCommand::COMPANY));
    entityHandler.addToArray(std::make_unique<Infantry>(Position(400, 100), LevelOfCommand::PLATOON));

    gameLoop(&game, &render, &inputHandler, &cam, &entityHandler, &eventHandler);

    GameCleanup();
    return 0;
}
