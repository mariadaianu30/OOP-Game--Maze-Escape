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


class LabyrinthRoom : public Room
{
protected:

	std::mt19937 rng;
	std::vector<cell> diamonds;
	std::vector<cell>coins;





public:
	LabyrinthRoom();
	LabyrinthRoom(const LabyrinthRoom& other) {};
	~LabyrinthRoom();
	void generateLayout() override;
	void generateMaze(int x, int y);
	bool inRange(int x, int y);
	const std::vector<std::vector<int>> getRoomLayout() override;
	void Draw() override;

	void spawnLoot(int diamondCount, int coinCount);
	void Update() override;
	bool isExitCell(int x, int y) const;
	void Regenerate();
	inline void sealCeiling();

};
