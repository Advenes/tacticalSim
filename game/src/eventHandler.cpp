#include "eventHandler.h"

id OrderHandler::addOrder(std::unique_ptr<Order> order) {
	order->orderId = nextID;
	nextID++;
	orders[order->getId()] = std::move(order);
	return (nextID - 1);
}

void MovingOrder::addMovingPoint(MovePoint point) {
	points.push(point);
}

void MovingOrder::removeMovingPoint() {
	if (!points.empty()) {
		points.pop();
	}
}

void OrderHandler::checkForBlankOrders() {
	for(auto order& : )
}

void OrderHandler::updateOrders() {

}

id Order::getId() {
	return orderId;
}