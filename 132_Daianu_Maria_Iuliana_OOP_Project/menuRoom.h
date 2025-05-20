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
	const float WARN_DURATION = 2.0f;
	char warnMessage[50];
	char playerName[16];



public:
	MenuRoom(const char* backgroundPath, const char* playButtonPath, const char* exitButtonPath, const char* fontPath);
	MenuRoom(const MenuRoom& other);

	~MenuRoom();
	void Draw() override;
	void Update()  override;
	void HandleInput();
	void HandleMouseHover(Vector2 mousePos);
	void HandleMouseClick(Vector2 mousePos);
	bool shouldExit();
	bool StartGame();
	const char* getPlayerName() const { return playerName; } // Getter for playerName
	void validatePlayerName() const; // Check if the name is valid
	void   triggerWarning(const char* msg);        //  ? aceasta e metoda
};