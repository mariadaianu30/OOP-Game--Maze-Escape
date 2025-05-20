#pragma once
#include <iostream>
#include "room.h"
#include "playerFrame.h"
#include "button.h"
#include "pickCharacter.h"
class PlayerRoom :public Room
{
protected:
	PlayerFrame playerGirl;
	PlayerFrame playerBoy;
	Button playButton;
	const char* character;
	Texture2D thanks = safeLoadTexture("Graphics/thanks.png");
	bool showThanksGirl = false;
	bool showThanksBoy = false;
	bool start;


public:
	PlayerRoom(const char* backgroundPath, const char* fontPath);
	~PlayerRoom() {};
	void Draw() override;
	void HandleStart();
	bool startGame();
	const char* HandleClick();
	const char* getCharacter() { return character; }
	void checkIfPicked();
	void HandleHover();

};