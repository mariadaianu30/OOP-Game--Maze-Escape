#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include "room.h"
#include "enemy.h"
#include "menuRoom.h"
#include "resources.h"
#include "player.h"

class ChestRoom :public Room
{
private:
	std::mt19937 rng;
	std::vector<cell>chests;
	std::vector<cell>obstacles;
	std::vector<Enemy>enemies;
	float chestRoomTime = 5.f;
	const char* enemyPath = "Graphics/enemy.png";
	Texture2D enemyTex{};

public:
	ChestRoom();
	~ChestRoom();
	void generateLayout() override;
	const std::vector<std::vector<int>> getRoomLayout() override;
	void Draw() override;
	void Update(Player* player);
	void generateChests(int chestCount, int minDist);
	void generateObstacles(int obstacleCount, int minDist);
	void generateEnemies(int enemyCount);
	void enemyCollision(Player* player);
	void Regenerate();
	static inline int dist2(const cell& a, const cell& b)
	{
		int dx = a.x - b.x;
		int dy = a.y - b.y;
		return dx * dx + dy * dy;
	}
};