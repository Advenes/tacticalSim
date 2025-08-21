#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include <unordered_map>
#include <memory>
#include "eventHandler.h"

enum class Type {
	TYPENULL = 0,
	UNIT = 1
};

enum class AmmoUsage {
	SAVEAMMO = 0,
	BALANCED = 1,
	MAXUSAGE = 2
};

enum class Experience {
	CONSCRIPT = 0,
	REGULAR = 1,
	EXPIERENCED = 2,
	VETERANS = 3
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
	int x, y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}
};

// Single Entity

class Entity { 
public:
	int id;
	Position pos;
	Type type;

	Entity(Position pos_, Type type_) {
		pos.x = pos_.x;
		pos.y = pos_.y;
		type = type_;
	}

	virtual ~Entity() {}

	static Texture2D svgToPng(std::string path);
};

class Unit : public Entity {
public:
	short int unsigned static const paramsCount = 13;
	int speed;
	int organization;
	int ammo;
	int food;
	int entrenchment;
	int exhaustion;
	int morale;
	int softAttack;
	int hardAttack;
	int hardness;
	int manpower;
	bool comunication;
	Experience experience;
	Order* currentOrder = new Order;
	uint8_t step = 0;

	Texture2D texture;
	LevelOfCommand levelOfCommand;

	Unit(Position pos_, LevelOfCommand level) : Entity(pos_, Type::UNIT) {
		levelOfCommand = level;
		switch (level) {
		case LevelOfCommand::SQUAD:
			manpower = 10;
			break;
		case LevelOfCommand::PLATOON:
			manpower = 40;
			break;
		case LevelOfCommand::COMPANY:
			manpower = 200;
			break;
		case LevelOfCommand::BATTALION:
			manpower = 1000;
			break;
		case LevelOfCommand::REGIMENT:
			manpower = 2000;
			break;
		case LevelOfCommand::BRIGADE:
			manpower = 5000;
			break;
		}
	}

	~Unit() {
		delete currentOrder;
	}

	void addOrder(Order* order);
	void clearOrder();
};

class Infantry : public Unit {
public:
	short int Portrait;
	Infantry(Position pos_, LevelOfCommand level) : Unit(pos_, level) {
		std::string path = "C:/Users/Admin/Desktop/tacticalSim/game/images/entities/tacticalIcons/infantry.svg";
		texture = svgToPng(path);
		Portrait = rand() % 8;

		// setting up the values
		speed = 4;
		organization = 100;
		ammo = 100;
		food = 100;
		entrenchment = 0;
		exhaustion = 0;
		morale = 100;
		softAttack = 25;
		hardAttack = 5;
		hardness = 0;
		comunication = true;
		experience = Experience::REGULAR;

	}
	~Infantry() {
		UnloadTexture(texture);
	}
};

// Move Point

// Entity handler

class EntityHandler {
public:
	std::vector<std::unique_ptr<Entity>> unitsArr;
	std::vector<Unit*> selectedUnits;
	std::unordered_map<int, bool> selectedUnitsMap;
	int nextId = 0;

	EntityHandler() {}

	void addToArray(std::unique_ptr<Entity> entity);
	void removeFromArray(int id);
	void CoutArr();
};
