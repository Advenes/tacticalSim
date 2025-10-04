#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include <unordered_map>
#include <memory>
#include "../entity.h"


class EntityHandler {
public:
    std::vector<std::unique_ptr<Unit>> unitsArr;

    EntityHandler() {}
    
    template<typename T>
    void createUnit(int id, Position pos, LevelOfCommand level) {
        static_assert(std::is_base_of<Unit, T>::value,"T must derive from Unit"); // static assert if T not deriving from Unit
        unitsArr.push_back(std::make_unique<T>(id, pos, level));
    }
    void removeFromArray(int id);
    void CoutArr();
    
    std::vector<Unit*> selectedUnits;
    std::unordered_map<int, bool> selectedUnitsMap;
private:
    int nextId = 0;
};
