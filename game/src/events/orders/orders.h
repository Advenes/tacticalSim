#pragma once
#include <unordered_map>
#include <memory>
#include <list>
#include "entities/entityHandler/entityHandler.h"
#include "entities/entity.h"
#include "inputs/inputState.h"
#include "camera/camera.h"

using id = uint32_t;

class MovePoint {
public:
    int x;
    int y;
    MovePoint(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};
    
class Order {
public:

    Order() {}
    virtual ~Order() = default;
    
    virtual bool execute() = 0;

    id getId();
    void setId(id _id);

private:
    id orderId = 0;
};

enum class Speed {
    SLOW = 0,
    NORMAL = 1,
    FAST = 2
};

class MovingOrder : public Order {
public:
    std::unordered_map<Unit*, std::list<MovePoint>::iterator> unitsFollowing;
    
    MovingOrder() : Order() {}
    std::list<MovePoint> points;

    bool execute() override;
    void addMovingPoint(MovePoint point);
    void removeLastMovingPoint();

    Speed getSpeed(){
        return ordersSpeed;
    }
    void setSpeed(Speed speed){
        ordersSpeed = speed;
    }
    
private:
    Speed ordersSpeed;
};

class AttackOrder : public Order{
public:
    std::unordered_map<Unit*, Unit*> unitsFollowingAndAttacked;
    
    AttackOrder() : Order() {}
    Unit* attackedUnit;
    
    bool execute() override;
    
private:

};
