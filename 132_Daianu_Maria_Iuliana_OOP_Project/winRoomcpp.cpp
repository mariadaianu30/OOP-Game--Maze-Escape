#include "winRoom.h"

WinRoom::WinRoom(const char* backgroundPath, const char* fontPath, const char* replayPath) : replayButton(replayPath, { 330,500 }, 0.23)
{
	replay = false;
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
}

WinRoom::~WinRoom()
{
	UnloadTexture(background);
	replayButton.~Button();
	UnloadFont(font);
}

void WinRoom::Draw()
{
	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "You won!", { 350, 400 }, 60, 3, WHITE);
	replayButton.DrawButton();
}