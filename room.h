#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include "resources.h"

enum class GameScreen { MENU, PLAYER, MAZE, TREASURE, WIN, LOSE };
class Room
{
protected:
	struct cell { int x, y; };
	std::string roomName;
	int roomCode;
	std::vector<std::vector<int>> roomLayout;
	Texture2D background;
	Texture2D wallTexture;
	const float WARN_DURATION = 2.0f;
	char warnMessage[50];
	Font font;
	static const int cellSize = 25;
	static const int cellCount = 35;
	static const int windowSize = cellSize * cellCount;
	float warnTimer;

public:
	Room();
	Room(const Room& other);
	virtual ~Room();
	virtual void generateLayout();
	virtual const std::vector<std::vector<int>> getRoomLayout()
	{
		return roomLayout;
	};
	virtual void Draw();
	virtual void Load();
	virtual void Update();

	static const int getWindowSize()
	{
		return windowSize;
	};
	virtual void triggerWarning(const char* msg);
	virtual void Load(const char* groundPath, const char* wallPath, const char* fontPath);
};