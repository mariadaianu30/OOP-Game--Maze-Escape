#pragma once
#include<iostream>
#include<cstring>
#include <exception>
#include <raylib.h>
#include "button.h"
#include "room.h"
#include "gameException.h" 
#include "nameMissing.h"
#include "resources.h"

class MenuRoom : public Room
{
private:

	Button playButton;
	Button exitButton;
	Rectangle inputBox;
	int letters;
	bool focusText;
	bool exit;
	bool startGame;
	char playerName[10];
	Texture2D inputBackground;



public:
	MenuRoom(const char* backgroundPath, const char* playButtonPath, const char* exitButtonPath, const char* fontPath, const char* inputPath);


	~MenuRoom();
	void Draw() override;
	void HandleInput();
	void HandleMouseHover(Vector2 mousePos);
	void HandleMouseClick(Vector2 mousePos);
	bool shouldExit();
	bool StartGame();
	const char* getPlayerName() const { return playerName; } // Getter for playerName
	void validatePlayerName() const; // Check if the name is valid
	const char* getPlayerName() { return playerName; };
};