#pragma once
#include <exception>
#include <raylib.h>
#include "button.h"
#include "room.h"
#include "gameException.h" 
#include "nameMissing.h"
#include "resources.h"
#include "observer.h"

class WinRoom : public Room, virtual public Observer
{
private:
	Button exitButton;
	Texture2D reward = { 0 };
	std::string currentRewardPath;

public:
	WinRoom(const char* backgroundPath, const char* fontPath);
	~WinRoom() override;
	void Draw() override;
	void HandleHover();
	bool HandleClickExit();
	void update(int score) override;
};