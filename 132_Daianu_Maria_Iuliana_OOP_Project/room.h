#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>

enum class GameScreen { MENU, MAZE, TREASURE, WIN, LOSE };
class Room
{
protected:
	std::string roomName;
	int roomCode;
	std::vector<std::vector<int>> roomLayout;
	Texture2D background;
	Texture2D wallTexture;
	Font font;
	int cellSize = 25;
	int cellCount = 35;
	int windowSize = cellSize * cellCount;
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
	virtual void Update() {};


};