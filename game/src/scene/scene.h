    #pragma once
    #include <iostream>
    #include "raylib.h"
    #include "render/render.h"
    #include "camera/camera.h"
    #include "inputs/inputState.h"
    #include "inputs/inputHandler.h"
    #include "textures/textureManager.h"
    #include "entities/entity.h"

    class Scene{
    private:
        EntityHandler* entityHandler;
        
    public:
        Scene(EntityHandler* _entityHandler) : entityHandler(_entityHandler) {
            createUnit<Infantry>(1, {200, 200}, LevelOfCommand::PLATOON);
            createUnit<Infantry>(2, {400, 250}, LevelOfCommand::SQUAD);
            createUnit<Infantry>(3, {600, 250}, LevelOfCommand::SQUAD, false);
            
        }
        ~Scene(){
        }
        
        void renderScene(InputState* inputState);

        template<typename T>
        void createUnit(int id, Position pos, LevelOfCommand level, bool ally = true){
            entityHandler->createUnit<T>(id, pos, level, ally);
        }
        
        Cam* getCamera(){
            return &camera;
        }

    private:
        
        void renderEntities();
        void renderInputs(InputState* inputState);
        void renderBackground();
            
        int getSceneWidth();
        int getSceneHeight();

        Cam camera;
        int backgroundX, backgroundY = 0;
        float hudScale = 1.0f;
    };
