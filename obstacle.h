#pragma once
#include <iostream>
#include <vector>
#include "object.h"
#include "resources.h"

class Obstacle : public Object
{
protected:
	std::vector<Cell> obstacles;
	int totalObstacles = 0;

public:
	Obstacle(const std::vector < std::vector<int>>& maze);
	~Obstacle();
	void DrawObject() override;
	void CollisionObstacle(int row, int col);
	void Load();

};