#pragma once
#include <iostream>
#include <vector>
#include "object.h"
#include "resources.h"

class Coin : public Object
{
protected:
	std::vector<Cell> coins;
	int totalCoins = 0;

public:
	Coin(const std::vector < std::vector<int>>& maze);
	~Coin();
	void DrawObject() override;
	void UpdateObject(const std::vector<std::vector<int>>& maze) override;
	void CollectCoinAt(int row, int col);
	void Load();

};