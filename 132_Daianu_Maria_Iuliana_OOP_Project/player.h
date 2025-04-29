#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <raylib.h>
#include "object.h"
#include "diamond.h"
#include "labyrinthRoom.h"
#include "resources.h"	

class Diamond;
class Player : public Object
{
protected:
	int diamondCount = 0;
	std::vector < std::vector<int>>diamondsCollected;
	Diamond* diamondSystem;

public:
	Player(int col, int row, Diamond* d);
	~Player();
	void UpdateObject(const std::vector < std::vector<int>>& maze) override;
	void DrawObject() override;
	int getDiamondCount() { return diamondCount; };
	bool hasWon(const LabyrinthRoom& room, const Diamond& diamMgr) const;
};