#include "entityHandler.h"

void EntityHandler::removeFromArray(int id) {
    for (int i = 0; i < unitsArr.size(); i++) {
        if (id == unitsArr[i]->getId()) {
            std::swap(unitsArr[i], unitsArr.back());
            unitsArr.pop_back();
            break;
        }
    }
}

void EntityHandler::CoutArr() {
    for (int i = 0; i < unitsArr.size(); i++) {
        std::cout << unitsArr[i]->getId() << " ";
    }
    std::cout << '\n' << unitsArr.size();
}

