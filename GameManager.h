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
#include "EnoughLives.h"
#include "scoreManager.h"


class GameManager {
private:
	void HandleMenu();
	void HandlePlayerSelect();
	void HandleMaze();
	void HandleWin();
	void HandleLose();
	void HandleTreasure();
	bool OneDiamond = true;
	static constexpr float TIME_LIMIT = 150.f;
	GameScreen currentScreen = GameScreen::MENU;
	GameScreen lastScreen = GameScreen::MENU;
	float playTime = 0.f;
	bool finished = false;
	bool mazeActive = false;
	Texture2D heart = safeLoadTexture("Graphics/heart.png");
	LabyrinthRoom myLab;
	PlayerRoom myPlayerRoom;
	Diamond myDiamond;
	Coin myCoin;
	Player* myPlayer = nullptr;
	LoseRoom myLoseRoom;
	WinRoom myWinRoom;
	ChestRoom myChestRoom;
	Chest<std::string> myChest;
	Obstacle myObstacle;
	ScoreManager scoreManager;
	bool wantExit = false;
	float delta = GetFrameTime();
	static constexpr float CHEST_LIMIT = 100.f;
	float chestTimeLeft = CHEST_LIMIT;
	bool showRetryWarning = false;
	float retryWarnTimer = 0.0f;


public:
	GameManager();
	~GameManager();
	void UpdateGame();
	void DrawGame();
	void ResetGame();
	bool getExit() { return wantExit; };
};