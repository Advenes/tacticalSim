#pragma once
#include "../eventHandler.h"
#include "orders.h"

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
