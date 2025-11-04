#include "orders.h"

bool MovingOrder::execute(){
    if(unitsFollowing.empty()){
        return false;
    }
    
    for (auto itUnit = unitsFollowing.begin(); itUnit != unitsFollowing.end(); ) {
        auto& unit = itUnit->first;
        auto& pointIt = itUnit->second;

        if (unit->getCurrentOrder() != this) {
            itUnit = unitsFollowing.erase(itUnit);
            continue;
        }

        MovePoint& targetPoint = *pointIt;

        if (int(unit->getPosition().x) == targetPoint.x && int(unit->getPosition().y) == targetPoint.y) {
            std::cout << "finished walking to a point" << '\n';
            ++pointIt;

            if (pointIt == points.end()) {
                itUnit = unitsFollowing.erase(itUnit);
                continue;
            }
        }

        if (pointIt != points.end()) {
            Position current = unit->getPosition();
            float dx = pointIt->x - current.x;
            float dy = pointIt->y - current.y;

            float stepX = (dx == 0) ? 0 : (dx > 0 ? 0.05f : -0.05f) * unit->values.speed;
            float stepY = (dy == 0) ? 0 : (dy > 0 ? 0.05f : -0.05f) * unit->values.speed;;

            stepX *= (static_cast<int>(getSpeed()) + 1);
            stepY *= (static_cast<int>(getSpeed()) + 1);

            unit->setPosition({ current.x + stepX, current.y + stepY });
        }

        ++itUnit;
    }
    return true;
}


bool AttackOrder::execute(){
    return true;
}
