#pragma once
#include "raylib.h"
#include "labyrinthRoom.h"
#include "menuRoom.h"
#include "playerRoom.h"
#include "winRoom.h"
#include "loseRoom.h"
#include "diamond.h"
#include "coin.h"
#include "player.h"
#include "notEscaped.h"
#include "chestRoom.h"
#include "chest.h"
#include "obstacle.h"


class GameManager {
private:
	void HandleMenu();
	void HandlePlayerSelect();
	void HandleMaze();
	void HandleWin();
	void HandleLose();
	void HandleTreasure();

	static constexpr float TIME_LIMIT = 1.f;
	GameScreen currentScreen = GameScreen::MENU;
	GameScreen lastScreen = GameScreen::MENU;
	float playTime = 0.f;
	bool finished = false;
	bool mazeActive = false;
	Texture2D heart = safeLoadTexture("Graphics/heart.png");
	LabyrinthRoom myLab;
	MenuRoom myMenu;
	PlayerRoom myPlayerRoom;
	Diamond myDiamond;
	Coin myCoin;
	Player* myPlayer = nullptr;
	LoseRoom myLoseRoom;
	WinRoom myWinRoom;
	ChestRoom myChestRoom;
	Chest myChest;
	Obstacle myObstacle;
	bool wantExit = false;
	float delta = GetFrameTime();
	static constexpr float CHEST_LIMIT = 50.f;
	float chestTimeLeft = CHEST_LIMIT;

public:
	GameManager();
	~GameManager();
	void UpdateGame();
	void DrawGame();
	void ResetGame();
	bool getExit() { return wantExit; };
};