#pragma once
#include <exception>
#include <raylib.h>
#include "button.h"
#include "room.h"
#include "gameException.h" 
#include "nameMissing.h"
#include "resources.h"

class WinRoom : public Room
{
private:
	Button exitButton;

public:
	WinRoom(const char* backgroundPath, const char* fontPath);
	~WinRoom() override;
	void Draw() override;
	void HandleHover();
	bool HandleClickExit();
};