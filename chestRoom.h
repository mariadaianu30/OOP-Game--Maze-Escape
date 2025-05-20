#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include "room.h"
#include "menuRoom.h"
#include "resources.h"

class ChestRoom :public Room
{
private:
	std::mt19937 rng;
	std::vector<cell>chests;
	std::vector<cell>obstacles;

public:
	ChestRoom();
	~ChestRoom() {};
	void generateLayout() override;
	const std::vector<std::vector<int>> getRoomLayout() override;
	void Draw() override;
	void generateChests(int chestCount);
	void generateObstacles(int obstacleCount);

};