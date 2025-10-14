#include "eventHandler.h"



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

void OrderHandler::checkForBlankOrders() {
    for (auto it = orders.begin(); it != orders.end(); ) {
        if (it->second->unitsFollowing.empty()) {
            it = orders.erase(it);
        } else {
            ++it;
        }
    }
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
    for (auto it = orderHandler.orders.begin(); it != orderHandler.orders.end(); it++) {
            it->second->execute();
    }
    orderHandler.checkForBlankOrders();
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
            
            unit->setCurrentOrder(order);
            orderHandler.orders[orderId]->unitsFollowing[unit] = movingOrder->points.begin();
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
            unit->setCurrentOrder(movingOrder);
            orderHandler.orders[orderId]->unitsFollowing[unit] = movingOrder->points.begin();
        }
        
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
        
        if (position.x  + (width * scale) >= minX && position.x <= maxX && position.y + (height * scale) >= minY && position.y  <= maxY) {
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

void EventHandler::removeUnitsFromOrder(){
    for (const auto& unitPtr : entityHandler->selectedUnits) {
        unitPtr->setCurrentOrder();
        std::cout << "removed order from unit: " << unitPtr->getId() << '\n';
    }
}
