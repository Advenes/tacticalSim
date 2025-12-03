#include "inputHandler.h"


void InputHandler::inputReciever() {
    float wheelMove = GetMouseWheelMove();
    float zoomMagnifier = 0.05f;

//    std::cout << '\n' << cam->getZoom() << '\n';
    float centerX = GetScreenWidth() / 2.0f / cam->getZoom();
    float centerY = GetScreenHeight() / 2.0f / cam->getZoom();

    if (wheelMove > 0) {
        cam->setZoom(cam->getZoom() + zoomMagnifier  * cam->getZoom());

        float newCenterX = GetScreenWidth() / 2.0f / cam->getZoom();
        float newCenterY = GetScreenHeight() / 2.0f / cam->getZoom();

        cam->setTargetX(cam->getTargetX() + (centerX - newCenterX));
        cam->setTargetY(cam->getTargetY() + (centerY - newCenterY));
    }

    else if (wheelMove < 0) {
        Vector2 bounds = cam->getCameraBound();

        if (((cam->getZoom() - zoomMagnifier) * bounds.y > GetScreenHeight()) &&
            (cam->getZoom() - zoomMagnifier) * bounds.x > GetScreenWidth()) {
            cam->setZoom(cam->getZoom() - (zoomMagnifier * cam->getZoom()));

            float newCenterX = GetScreenWidth() / 2.0f / cam->getZoom();
            float newCenterY = GetScreenHeight() / 2.0f / cam->getZoom();

            cam->setTargetX(cam->getTargetX() + (centerX - newCenterX));
            cam->setTargetY(cam->getTargetY() + (centerY - newCenterY));
        }
    }

    // Movement logic (no moveTarget)
    float viewW = GetScreenWidth() / cam->getZoom();
    float viewH = GetScreenHeight() / cam->getZoom();
    
    float maxX = cam->getCameraBound().x - viewW;
    float maxY = cam->getCameraBound().y - viewH;

    float x = cam->getTargetX();
    float y = cam->getTargetY();

    // WASD movement
    if (IsKeyDown(KEY_W) && y > 0) y -= std::max<int>(10 / cam->getZoom(), 2);
    if (IsKeyDown(KEY_S) && y < maxY) y +=  std::max<int>( 10  / cam->getZoom(), 2);
    if (IsKeyDown(KEY_A) && x > 0) x -= std::max<int>(10  / cam->getZoom(), 2);
    if (IsKeyDown(KEY_D) && x < maxX) x += std::max<int>(10  / cam->getZoom(), 2);

//    std::cout << maxX << " " << maxY << '\n';
//    std::cout << "views " << viewH << " " << viewW << '\n';
//
    // Edge-scrolling
    if (GetMouseX() > GetScreenWidth() - 10 && x < maxX) x += 2;
    else if (GetMouseX() < 10 && x > 0) x -= 2;

    if (GetMouseY() < 10 && y > 0) y -= 2;
    else if (GetMouseY() > GetScreenHeight() - 10 && y < maxY) y += 2;
    
    // Clamp just in case
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > maxX) x = maxX;
    if (y > maxY) y = maxY;

//    std::cout << cam->getTargetY() << cam->getTargetX();
    cam->setTargetX(x);
    cam->setTargetY(y);
    
    if(IsKeyDown(KEY_SPACE)){
        if(!inputState.timeKeyPressed){
            inputState.timeKeyPressed = true;
            GameTime::get().switchTime();
            std::cout << "switched";
        }
    }
    else{
        inputState.timeKeyPressed = false;
    }
}

void InputHandler::mouseInput() {

    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !inputState.selecting){
        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
        if(!eventHandler->selectOneUnit(mouseWorld, cam)){
            inputState.selecting = true;
            inputState.selPos.x = mouseWorld.x;
            inputState.selPos.y = mouseWorld.y;
        }
        
    }
    
    if(IsKeyPressed(KEY_H)){
        eventHandler->removeUnitsFromOrder();
    }
    
//    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
//            eventHandler->
//    }
    
    // selecting
    if (inputState.selecting && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        
        inputState.selecting = false;
        
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !inputState.selecting) {
             GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
            inputState.selPos.x = mouseWorld.x;
            inputState.selPos.y = mouseWorld.y;
            inputState.selecting = true;
        }
        eventHandler->selectingUnits(mouseWorld, inputState, cam);
    }
    
    if(IsKeyDown(KEY_M) && !inputState.measuring){
        inputState.measuring = true;
        inputState.measPos = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
    }
    
    if(inputState.measuring){
        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
        eventHandler->measureDistance(mouse, &inputState, cam);
    }
    
    if(inputState.measuring && !IsKeyDown(KEY_M)){
        inputState.measuring = false;

    }
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !IsKeyDown(KEY_LEFT_SHIFT)){
        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
        if(!eventHandler->attackUnit(mouse, cam)){
            eventHandler->givingOrders(cam);
        }
    }
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT)){
        eventHandler->addToOrders(cam);
    }
}

