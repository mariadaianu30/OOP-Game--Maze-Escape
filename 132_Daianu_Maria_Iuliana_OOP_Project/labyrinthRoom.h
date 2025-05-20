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

struct cell { int x, y; };
class LabyrinthRoom : public Room
{
protected:

	std::mt19937 rng;
	std::vector<cell> diamonds;
	bool spawned;



public:
	LabyrinthRoom();
	LabyrinthRoom(const LabyrinthRoom& other);
	~LabyrinthRoom();
	void generateLayout() override;
	void generateMaze(int x, int y);
	bool inRange(int x, int y);
	const std::vector<std::vector<int>> getRoomLayout() override;
	void Draw() override;
	void Load(const char* groundPath, const char* wallPath, const char* fontPath);
	void spawnDiamonds(int diamondCount);
	void Update() override;
	bool isExitCell(int x, int y) const;
};
