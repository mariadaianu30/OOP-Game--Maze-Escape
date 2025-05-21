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
#include "coin.h"
#include "chest.h"
#include "obstacle.h"

class Diamond;
class Player : public Object
{
protected:
	int diamondCount = 0;
	std::vector < std::vector<int>>diamondsCollected;
	Diamond* diamondSystem;

	int coinCount = 0;
	std::vector <std::vector<int>>coinsCollected;
	Coin* coinSystem;
	int lives;
	int coins;
	Chest* chestSystem;
	std::vector <std::vector<int>>chestsCollected;
	Obstacle* obstacleSystem;
	std::vector < std::vector<int>>obstaclesCollisioned;
	float& timeLeft;



public:
	Player(int col, int row, const char* characterPath, Diamond* d, Coin* c, Chest* ch, Obstacle* o, int existingLives, int existingCoins, float& levelTimer);
	~Player();
	void UpdateObject(const std::vector < std::vector<int>>& maze) override;
	void DrawObject() override;
	int getDiamondCount() { return diamondCount; };

	int getCoin() {
		return coins;
	};

	bool hasWon(const LabyrinthRoom& room, const Diamond& diamMgr) const;
	void loseLife();
	bool lifeLost();
	void buyLife();
	int getLives() { return lives; };
	bool inBounds(int x, int y);
	float getXplayer() { return position.x; };
	float getYplayer() { return  position.y; };

};