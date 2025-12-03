#pragma once
#include <unordered_map>
#include <memory>
#include <list>
#include "entities/entityHandler/entityHandler.h"
#include "entities/entity.h"
#include "inputs/inputState.h"
#include "camera/camera.h"
#include "orders/orderHandler.h"
#include "utis/rangePoints.h"
#include <set>
#include <cmath>
#include <raylib.h>

class EventHandler {
public:
    EventHandler(EntityHandler* _entityHandler){
        entityHandler = _entityHandler;
    }
	OrderHandler orderHandler;
    
    void executeOrders();
    
    void addToOrders(Cam* cam);
    
    void givingOrders(Cam* cam);
    
    void selectingUnits(Vector2 mouseWorld, InputState inputState, Cam* camera);
    
    bool selectOneUnit(Vector2 mouseWorld, Cam* camera);
    
    bool attackUnit(Vector2 mouseWorld, Cam* camera);

    void measureDistance(Vector2 mouse, InputState* inputState, Cam* camera);
    
    void removeUnitsFromOrder();
    
private:
    EntityHandler* entityHandler;
};
