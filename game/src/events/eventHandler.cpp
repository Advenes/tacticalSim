#include "eventHandler.h"

#ifndef FOREST_COLOR
#define FOREST_COLOR
const Color FOREST = {15, 88, 25, 255};
#endif

#ifndef FIELD_COLOR
#define FIELD_COLOR
const Color FIELD  = {211, 209, 9, 255};
#endif

#ifndef CITY_COLOR
#define CITY_COLOR
const Color CITY   = {177, 103, 5, 255};
#endif

#ifndef COLOR_EQ_OPERATOR
#define COLOR_EQ_OPERATOR
inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
#endif
id OrderHandler::addOrder(std::unique_ptr<Order> order) {
	order->setId(nextID);
	nextID++;
	orders[order->getId()] = std::move(order);
	return (nextID - 1);
}

void MovingOrder::addMovingPoint(MovePoint point) {
	points.push_back(point);
}

void MovingOrder::removeLastMovingPoint() {
    points.pop_back();
}

void OrderHandler::updateOrders() {

}

id Order::getId() {
	return orderId;
}

void Order::setId(id _id) {
	orderId = _id;
}


void EventHandler::executeOrders() {
    std::set<int> idsToErase;
    for (auto it = orderHandler.orders.begin(); it != orderHandler.orders.end(); it++) {
        if (!it->second->execute()) {
            idsToErase.insert(it->second->getId());
        }
    }
// erase orders
    for (auto it = orderHandler.orders.begin(); it != orderHandler.orders.end();) {
        if (auto search = idsToErase.find(it->second->getId()); search != idsToErase.end()) {
            it = orderHandler.orders.erase(it);
        }
        else{
            it++;
        }
    }
}

void EventHandler::addToOrders(Cam* cam){
    for(auto &unit : entityHandler->selectedUnits){
        if(unit->getCurrentOrder() == nullptr){
            id orderId = orderHandler.addOrder(std::make_unique<MovingOrder>());
            Order* order = orderHandler.orders[orderId].get();
            
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
            MovingOrder* movingOrder = dynamic_cast<MovingOrder*>(order);
            movingOrder->addMovingPoint(MovePoint(mouseWorld.x, mouseWorld.y));
            movingOrder->setSpeed(Speed::NORMAL);
            
            unit->setCurrentOrder(movingOrder);
            movingOrder->unitsFollowing[unit] = movingOrder->points.begin();
//            orderHandler.orders[orderId]->unitsFollowing[unit] = movingOrder->points.begin();
            continue;
        }
        
        MovingOrder* movingOrder = dynamic_cast<MovingOrder*>(unit->getCurrentOrder());
        if(movingOrder){
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
            movingOrder->addMovingPoint(MovePoint(mouseWorld.x, mouseWorld.y));
            std::cout << "added point on: " << mouseWorld.x << " " << mouseWorld.y;
        }
    }
}

void EventHandler::givingOrders(Cam *cam){
    if(entityHandler->selectedUnits.size() > 0){

        std::cout << '\n' << "given an order to entities" << '\n';
        id orderId = orderHandler.addOrder(std::make_unique<MovingOrder>());
        Order* order = orderHandler.orders[orderId].get();

        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *cam->getCamera());
        MovingOrder* movingOrder = dynamic_cast<MovingOrder*>(order);
        movingOrder->addMovingPoint(MovePoint(mouseWorld.x, mouseWorld.y));
        movingOrder->setSpeed(Speed::NORMAL);
        
        for (auto unit : entityHandler->selectedUnits) {
            movingOrder->unitsFollowing[unit] = movingOrder->points.begin();
            unit->setCurrentOrder(movingOrder);
        }

        
//        for (auto unit : entityHandler->selectedUnits) {
//            unit->setCurrentOrder(movingOrder);
//            orderHandler.orders[orderId]->unitsFollowing[unit] = movingOrder->points.begin();
//        }
        
        std::cout << '\n' << movingOrder->points.front().x << ' ' << movingOrder->points.front().y << '\n';
        std::cout << "id: " << orderId << '\n';
    }
}



void EventHandler::selectingUnits(Vector2 mouseWorld, InputState inputState, Cam *cam){
    float startX = inputState.selPos.x;
    float startY = inputState.selPos.y;
    float endX = mouseWorld.x;
    float endY = mouseWorld.y;

    // Normalize rectangle
    float minX = std::min(startX, endX);
    float maxX = std::max(startX, endX);
    float minY = std::min(startY, endY);
    float maxY = std::max(startY, endY);

    entityHandler->selectedUnits.clear();
    entityHandler->selectedUnitsMap.clear();

    float scale = 0.55f / cam->getZoom();
    int width = TextureManager::get().getTexture("infantry")->width;
    int height = TextureManager::get().getTexture("infantry")->height;
    
    for (const auto& unitPtr : entityHandler->unitsArr) {
        Unit* unit = unitPtr.get();
        Position position = unit->getPosition();
        
        if (position.x  + (width * scale) >= minX && position.x <= maxX && position.y + (height  * scale) >= minY && position.y  <= maxY) {
            entityHandler->selectedUnits.push_back(unit);
            entityHandler->selectedUnitsMap.insert({ unit->getId(), true });
            std::cout << "added unit " << unit->getId() << '\n';
        }
    }
}

bool EventHandler::selectOneUnit(Vector2 mouseWorld, Cam* cam){
    for (const auto& unitPtr : entityHandler->unitsArr) {
        Unit* unit = unitPtr.get();
        Position position = unit->getPosition();
        float scale = 0.55f / cam->getZoom();

        int width = TextureManager::get().getTexture("infantry")->width;
        int height = TextureManager::get().getTexture("infantry")->height;
        
        if (mouseWorld.x > unit->getPosition().x && mouseWorld.x < unit->getPosition().x + (width * scale) &&
            mouseWorld.y > unit->getPosition().y && mouseWorld.y < unit->getPosition().y + (height * scale) ) {
            entityHandler->selectedUnits.erase(entityHandler->selectedUnits.begin(), entityHandler->selectedUnits.end());
            entityHandler->selectedUnitsMap.clear();
            
            entityHandler->selectedUnits.push_back(unit);
            entityHandler->selectedUnitsMap.insert({ unit->getId(), true });
            std::cout << "added unit " << unit->getId() << '\n';
            return true;
        }
    }
    return false;
}

bool EventHandler::attackUnit(Vector2 mouseWorld, Cam* cam){

    for (const auto& unitPtr : entityHandler->unitsArr) {
        if(unitPtr->isAlly()){
            continue;
        }
        Unit* unit = unitPtr.get();
        Position position = unit->getPosition();
        float scale = 0.55f / cam->getZoom();

        int width = TextureManager::get().getTexture("infantry")->width;
        int height = TextureManager::get().getTexture("infantry")->height;
        
        if (mouseWorld.x > unit->getPosition().x && mouseWorld.x < unit->getPosition().x + (width * scale) &&
            mouseWorld.y > unit->getPosition().y && mouseWorld.y < unit->getPosition().y + (height * scale) ) {
            
            id orderId = orderHandler.addOrder(std::make_unique<AttackOrder>());
            Order* order = orderHandler.orders[orderId].get();
            AttackOrder* attackOrder = dynamic_cast<AttackOrder*>(order);
            
            std::vector<Unit*> attackingUnits;
            for(auto& unitAttacking : entityHandler->selectedUnits){
                std::vector<MovePoint> points = getLinePoints(unitAttacking->getPosition().x, unitAttacking->getPosition().y, unit->getPosition().x, unit->getPosition().y, 5);
                
                if(checkForHeightObstructions({unitAttacking->getPosition().x, unitAttacking->getPosition().y}, {unit->getPosition().x, unit->getPosition().y}, points)){
                    std::cout << "height diff" << '\n';
                    continue;
                }
                
                if(checkForTerrainObstructions({unitAttacking->getPosition().x, unitAttacking->getPosition().y}, {unit->getPosition().x, unit->getPosition().y}, points, unitAttacking->values.maxEffectiveRange)){
                    std::cout << "terrain blocking" << '\n';
                    continue;
                }
                
                
                attackingUnits.push_back(unitAttacking);
            }
            
            for(auto& unitAttacking : attackingUnits){
                attackOrder->unitsFollowingAndAttacked[unitAttacking] = unit;
                unitAttacking->setCurrentOrder(attackOrder);
                std::cout << unitAttacking->getId() << " - unit Attacking -> " << unit->getId() << '\n';
                std::cout << "current order id: " <<unitAttacking->getCurrentOrder()->getId() << '\n';
            }
            if(!attackingUnits.empty()){
                return true;
            }
            
        }
    }
    return false;
}


void EventHandler::measureDistance(Vector2 mouse, InputState* inputState, Cam* camera){
    float distanceX = mouse.x - inputState->measPos.x;
    float distanceY = mouse.y - inputState->measPos.y;
    double realDistance = sqrt(pow(distanceX,2) + pow(distanceY,2)) * 3.35;
    inputState->measuringDistance = realDistance;
    std::cout << realDistance;
}

void EventHandler::removeUnitsFromOrder(){
    for (const auto& unitPtr : entityHandler->selectedUnits) {
        unitPtr->setCurrentOrder(nullptr);
        std::cout << "removed order from unit: " << unitPtr->getId() << '\n';
    }
}


