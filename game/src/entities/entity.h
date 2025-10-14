#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include <unordered_map>
#include <memory>

enum class AmmoUsage {
	SAVEAMMO = 0,
	BALANCED = 1,
	MAXUSAGE = 2
};

enum class Experience {
	CONSCRIPT = 0,
	REGULAR = 1,
	EXPIERENCED = 2,
	VETERAN = 3
};

enum class LevelOfCommand {
	LEVELNULL = 0,
	SQUAD = 1,
	PLATOON = 2,
	COMPANY = 3,
	BATTALION = 4,
	REGIMENT = 5,
	BRIGADE = 6,
	DIVISION = 7
};

class Position {
public:
	float x, y;
	Position(float x = 0, float y = 0) : x(x), y(y) {}
};

class Entity {
public:
    virtual ~Entity() {}

    virtual int getId() const = 0;
    virtual void setId(int id) = 0;

    virtual Position getPosition() const = 0;
    virtual void setPosition(const Position& pos) = 0;
};

struct MoreValues{
    int speed = 4;
    int organization = 100;
    int ammo = 100;
    int food = 100;
    int entrenchment = 0;
    int exhaustion = 0;
    int morale = 100;
    int softAttack = 25;
    int hardAttack = 5;
    int hardness = 0;
    bool comunication = true;
    Experience experience = Experience::REGULAR;
};

class Order;

class Unit : public Entity {
public:

    Unit(int id_, Position pos_, LevelOfCommand level_)
        : id(id_), pos(pos_), levelOfCommand(level_) {}

    virtual ~Unit() {}
    
    int getId() const override { return id; }
    void setId(int _id) override { id = _id; }

    Position getPosition() const override { return pos; }
    void setPosition(const Position& newPos) override { pos = newPos; }

    LevelOfCommand getLevelOfCommand() const { return levelOfCommand; }
    void setLevelOfCommand(LevelOfCommand level) { levelOfCommand = level; }

    virtual std::string getTextureID() const = 0;
    
    LevelOfCommand getLoc();
    
    Order* getCurrentOrder(){		
        return current_order;
    };
    void setCurrentOrder(Order* _order = nullptr){
        current_order = _order;
    };
    
    MoreValues values;
    
protected:
    int id;
    Position pos;
    LevelOfCommand levelOfCommand;
    Order* current_order = nullptr;
};


class Infantry : public Unit {
public:
	short int Portrait = rand() % 8;
    
	Infantry(int id, Position pos, LevelOfCommand level) : Unit(id, pos, level) {
	}
    
    std::string getTextureID() const override {
        return "infantry";
    }

};

