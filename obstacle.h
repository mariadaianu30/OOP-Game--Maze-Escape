#pragma once
#include <iostream>
#include <vector>
#include "object.h"
#include "resources.h"
#include <random>

class Obstacle : public Object
{
protected:
	std::vector<Cell> obstacles;
	int totalObstacles = 0;
	std::vector<int>      texIdx;
	std::vector<Texture2D> textures;


public:
	Obstacle(const std::vector < std::vector<int>>& maze);
	~Obstacle();
	void DrawObject() override;
	void Load();

};