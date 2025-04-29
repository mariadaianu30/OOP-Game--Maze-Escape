#pragma once
#include<iostream>
#include <cstring>
#include <vector>
#include <raylib.h>
#include <cstdlib>
#include <random>
#include "object.h"
#include "resources.h"
#include "player.h"

struct Cell { int x, y; };

class Diamond : public Object
{
private:
	std::vector<Cell>diamonds;
	int totalDiamonds = 0;

public:
	Diamond(const std::vector < std::vector<int>>& maze);
	~Diamond();

	void DrawObject() override;
	void UpdateObject(const std::vector<std::vector<int>>& maze) override;
	void CollectAt(int col, int row);
	int getTotal() const { return totalDiamonds; }
};
