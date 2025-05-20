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

	Chest* chestSystem;
	std::vector <std::vector<int>>chestsCollected;
	int coins;


public:
	Player(int col, int row, const char* characterPath, Diamond* d, Coin* c, Chest* ch, int existingLives, int existingCoins);
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
};