#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "Entity.h"

// Requires https://github.com/nlohmann/json package installation
#include <nlohmann/json.hpp>

using namespace nlohmann; // the one time I'll use a namespace ;)

class Level {
public:
	Level(std::string path);
	std::string getName() {
		return name;
	}
	int getId() {
		return id;
	}
	Vec2D getSize() {
		return size;
	}
	Vec2D getSpawn() {
		return spawn;
	}
	void setSpawn(Vec2D newSpawn) {
		spawn = newSpawn;
	}
	Entity* getObject(int x, int y);
public:
	std::vector<Entity*> statics;
	std::vector<Entity*> dynamics;
	std::vector<Entity*> drawables;
	std::vector<Entity*> interactables;
private:
	void readJson();
	void readGrid();
	Entity* createEntity(int id, Vec2D size, Vec2D destination);
private:
	json j;
	std::string name;
	int id;
	int rows, columns;
	Vec2D size, tileSize;
	Vec2D spawn;
	std::map<int, std::map<int, Entity*>> data;
};

