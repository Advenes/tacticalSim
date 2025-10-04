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
    std::unordered_map<Unit*, std::list<MovePoint>::iterator> unitsFollowing;
    Order() {}
    virtual ~Order() = default;
    
    virtual void execute() = 0;
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
    MovingOrder() : Order() {}
    std::list<MovePoint> points;

    void execute() override;
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
