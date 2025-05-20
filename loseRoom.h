#pragma once
#include <iostream>
#include<cstring>
#include <exception>
#include <raylib.h>
#include "button.h"
#include "room.h"
#include "gameException.h" 
#include "nameMissing.h"
#include "resources.h"

class LoseRoom : public Room
{
private:
	Button replayButton;
	Button exitButton;
	Button buyButton;
	bool replay;
public:
	LoseRoom(const char* backgroundPath, const char* fontPath);

	~LoseRoom() override;
	void Draw() override;
	void HandleHover();
	bool HandleClickReplay();
	bool HandleClickBuy();
	bool HandleClickExit();
};
