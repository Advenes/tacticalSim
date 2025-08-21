#pragma once
#include <unordered_map>
#include <memory>
#include <queue>

using id = uint32_t;

class MovePoint {
public:
	int x;
	int y;
	MovePoint(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

class Order {
public:
	id orderId = 0;
	Order() {}
	virtual ~Order() = default;
	id getId();
};

enum class Speed {
	SLOW = 0,
	NORMAL = 1,
	FAST = 2
};

class MovingOrder : public Order {
public:
	Speed ordersSpeed;
	std::queue<MovePoint> points;

	MovingOrder(Speed ordersSpeed_) : Order() {
		ordersSpeed = ordersSpeed_;
	}

	void addMovingPoint(MovePoint point);
	void removeMovingPoint();
};


class OrderHandler{
public:
	std::unordered_map<id, std::unique_ptr<Order>> orders;
	id nextID = 1;
	OrderHandler() {

	}
	~OrderHandler() {

	}

	void checkForBlankOrders();
	void updateOrders();

	id addOrder(std::unique_ptr<Order> order);

};

class EventHandler {
public:
	OrderHandler orderHandler;
};

