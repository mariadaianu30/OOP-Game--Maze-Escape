#pragma once
#include <iostream>
#include <vector>
#include "object.h"
#include "resources.h"

class Chest : public Object
{
protected:
	std::vector<Cell> chests;
	int totalChests = 0;

public:
	Chest(const std::vector < std::vector<int>>& maze);
	~Chest();
	void DrawObject() override;
	void UpdateObject(const std::vector<std::vector<int>>& maze) override;
	void CollectChestAt(int row, int col);
	void Load();

};