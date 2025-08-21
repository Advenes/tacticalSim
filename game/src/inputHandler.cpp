#include "inputHandler.h"


void InputHandler::inputReciever(Camera2D* cam, Render* render) {
    float wheelMove = GetMouseWheelMove();
    float zoomMagnifier = 0.1f;

    float centerX = GetScreenWidth() / 2.0f / cam->zoom;
    float centerY = GetScreenHeight() / 2.0f / cam->zoom;

    if (wheelMove > 0) {

        cam->zoom += (zoomMagnifier);

        float newCenterX = GetScreenWidth() / 2.0f / cam->zoom;
        float newCenterY = GetScreenHeight() / 2.0f / cam->zoom;

        cam->target.x += (centerX - newCenterX);
        cam->target.y += (centerY - newCenterY);
    }

    else if (wheelMove < 0 && ((cam->zoom - 0.1f) * render->getImageHeight() > GetScreenHeight())) {
        cam->zoom -= (zoomMagnifier * cam->zoom);

        float newCenterX = GetScreenWidth() / 2.0f / cam->zoom;
        float newCenterY = GetScreenHeight() / 2.0f / cam->zoom;

        cam->target.x += (centerX - newCenterX);
        cam->target.y += (centerY - newCenterY);

        float viewW = GetScreenWidth() / cam->zoom;
        float viewH = GetScreenHeight() / cam->zoom;

        if (cam->target.x < 0) cam->target.x = 0;
        if (cam->target.y < 0) cam->target.y = 0;

        if (cam->target.x + viewW > render->getImageWidth()) {
            cam->target.x = render->getImageWidth() - viewW;
        }

        if (cam->target.y + viewH > render->getImageHeight()) {
            cam->target.y = render->getImageHeight() - viewH;
        }
    }

    if (IsKeyDown(KEY_W) && cam->target.y > 0) cam->target.y -= 5;
    if (IsKeyDown(KEY_S) && cam->target.y + (GetScreenHeight() / cam->zoom) < render->getImageHeight()) cam->target.y += 5;
    if (IsKeyDown(KEY_A) && cam->target.x > 0) cam->target.x -= 5;
    if (IsKeyDown(KEY_D) && cam->target.x + (GetScreenWidth() / cam->zoom) < render->getImageWidth()) cam->target.x += 5;

    if (GetMouseX() > GetScreenWidth() - 10 && cam->target.x + (GetScreenWidth() / cam->zoom) < render->getImageWidth()) {
        cam->target.x += 2;
    }
    else if (GetMouseX() < 10 && cam->target.x > 0) {
        cam->target.x -= 2;
    }
    else if (GetMouseY() < 10 && cam->target.y > 0) {
        cam->target.y -= 2;
    }
    else if (GetMouseY() > GetScreenHeight() - 10 && cam->target.y + (GetScreenHeight() / cam->zoom) < render->getImageHeight()) {
        cam->target.y += 2;
    }
}

void InputHandler::mouseInput(EntityHandler* entityHandler, Camera2D* camera, EventHandler* eventHandler) {

    // selecting
    if (inputState.selecting && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        inputState.selecting = false;

        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera);

        float startX = inputState.selPos.x;
        float startY = inputState.selPos.y;
        float endX = mouseWorld.x;
        float endY = mouseWorld.y;

        // Normalize rectangle
        float minX = fminf(startX, endX);
        float maxX = fmaxf(startX, endX);
        float minY = fminf(startY, endY);
        float maxY = fmaxf(startY, endY);

        entityHandler->selectedUnits.clear();
        entityHandler->selectedUnitsMap.clear();

        for (int i = 0; i < entityHandler->unitsArr.size(); i++) {
            Entity* ent = entityHandler->unitsArr[i].get();
            int x = ent->pos.x;
            int y = ent->pos.y;

            if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
                entityHandler->selectedUnits.push_back(dynamic_cast<Unit*>(ent));
                entityHandler->selectedUnitsMap.insert({ ent->id, true });
                std::cout << "added unit " << entityHandler->unitsArr[i]->id << '\n';
            }
        }
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !inputState.selecting) {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera);
        inputState.selPos.x = mouseWorld.x;
        inputState.selPos.y = mouseWorld.y;
        inputState.selecting = true;
    }

    // giving units orders
    if(entityHandler->selectedUnits.size() > 0 && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

        std::cout << '\n' << "given an order to entities" << '\n';
        id orderId = eventHandler->orderHandler.addOrder(std::make_unique<MovingOrder>(Speed::NORMAL));
        Order* order = eventHandler->orderHandler.orders[orderId].get();
        for (auto unit : entityHandler->selectedUnits) {
            unit->currentOrder = order;
        }

        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera);
        MovingOrder* movingOrder = dynamic_cast<MovingOrder*>(order);
        movingOrder->addMovingPoint(MovePoint(mouseWorld.x, mouseWorld.y));
        
        std::cout << '\n' << movingOrder->points.front().x << ' ' << movingOrder->points.front().y << '\n';
        std::cout << "id: " << orderId << '\n';
    }
}