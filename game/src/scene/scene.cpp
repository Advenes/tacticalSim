#include "scene.h"

void Scene::renderScene(InputState* inputState){
    BeginMode2D(*camera.getCamera());
    renderBackground();
    renderInputs(inputState);
    renderEntities();
    EndMode2D();
}

void Scene::renderBackground(){
    Render::renderSprite(TextureManager::get().getBackground(), {0,0}, 1, WHITE);
}

void Scene::renderInputs(InputState *inputState){
    if (inputState->selecting) {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera.getCamera());
        float startX = inputState->selPos.x;
        float startY = inputState->selPos.y;
        float width = mouseWorld.x - startX;
        float height = mouseWorld.y - startY;

        // Optional: handle negative width/height if dragging left/up
        DrawRectangleLines(startX, startY, width, height, WHITE);
    }
    
    if(inputState->measuring){
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera.getCamera());
        DrawLineEx(inputState->measPos, mouseWorld, 1.0f / camera.getZoom(), WHITE);
        std::string distanceStr = std::to_string(inputState->measuringDistance);
        const char* text = distanceStr.c_str();
        std::cout << '\n' << "text: " << text << '\n';
        Vector2 mouse = GetMousePosition();
        mouse.y -= 20;
        Vector2 realMid = GetScreenToWorld2D(mouse, *camera.getCamera());
        DrawText(text, realMid.x, realMid.y, 20 / camera.getZoom(), WHITE);
    }

    if (inputState->measuring && IsKeyDown(KEY_H)) {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera.getCamera());
        int steps = 25;
        std::vector<MovePoint> points = getLinePoints(inputState->measPos.x, inputState->measPos.y, mouseWorld.x, mouseWorld.y, steps);
        if (checkForHeightObstructions(inputState->measPos, mouseWorld, points)) {
            DrawText("obstructed by height", mouseWorld.x + (20 / camera.getZoom()), mouseWorld.y, 20 / camera.getZoom(), RED);
        }
        if (checkForTerrainObstructions(inputState->measPos, mouseWorld, points, 200 / (steps / 5) )) {
            DrawText("obstructed by terrain", mouseWorld.x + (20 / camera.getZoom()), mouseWorld.y + (20 / camera.getZoom()), 20 / camera.getZoom(), RED);
        }
    }
}

void Scene::renderEntities(){
    for(auto& unit : entityHandler->unitsArr){
        Color color = WHITE;
        const int selectedUnitsShadowValue = 100;
        if(entityHandler->selectedUnitsMap[unit->getId()]){
            color.b -= 100;
            color.r -= 100;
            color.g -= 100;
        }

        Vector2 pos;
        pos.x = unit->getPosition().x;
        pos.y = unit->getPosition().y;
        
        Render::renderSprite(TextureManager::get().getTexture(unit->getTextureID()), pos, 0.65f / camera.getZoom(), color);

        // drawing level of command
        if (unit->getLevelOfCommand() != LevelOfCommand::LEVELNULL) {
            Vector2 locPos;
            float scale = 0.65f / camera.getZoom();
            locPos.x = pos.x + (2 * scale);
            locPos.y = pos.y - (45 * scale);

            Texture2D* txt;

            switch (unit->getLevelOfCommand()) {
                case LevelOfCommand::SQUAD:      txt = TextureManager::get().getTexture("squad"); break;
                case LevelOfCommand::PLATOON:    txt = TextureManager::get().getTexture("platoon"); break;
                case LevelOfCommand::COMPANY:    txt = TextureManager::get().getTexture("company"); break;
                case LevelOfCommand::BATTALION:  txt = TextureManager::get().getTexture("battalion"); break;
                case LevelOfCommand::REGIMENT:   txt = TextureManager::get().getTexture("regiment"); break;
                case LevelOfCommand::BRIGADE:    txt = TextureManager::get().getTexture("brigade"); break;
                case LevelOfCommand::DIVISION:   txt = TextureManager::get().getTexture("division"); break;
                default:
                    std::cout << "\nLOC NIE DZIALA: " << static_cast<int>(unit->getLevelOfCommand()) << '\n';
                    continue; // skip drawing LOC
            }

            Render::renderSprite(txt, locPos, 0.45f / camera.getZoom(), color);
            
        }
    }
}


