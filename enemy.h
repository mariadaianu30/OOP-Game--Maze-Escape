#pragma once
#include <raylib.h>
#include <random>
#include <vector>
#include "object.h"
#include "resources.h"

class Enemy : public Object
{
private:
	int frame = 0;
	int step = 15;
	const Texture2D* tex;
public:
	Enemy(int startX, int startY, Texture2D* sharedTex);
	void Update(const std::vector<std::vector<int>>& map, std::mt19937& rng);
	void Draw(float cellSize) const;
	bool inBounds(int x, int y);
	float getXenemy() { return position.x; };
	float getYenemy() { return position.y; };
};