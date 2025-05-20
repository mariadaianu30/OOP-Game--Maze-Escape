#include "loseRoom.h"


LoseRoom::LoseRoom(const char* backgroundPath, const char* fontPath, const char* replayPath) : replayButton(replayPath, { 330,500 }, 0.23)
{
	replay = false;
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
}

LoseRoom::~LoseRoom()
{
	UnloadTexture(background);
	replayButton.~Button();
	UnloadFont(font);
}

void LoseRoom::Draw()
{
	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "You lost!", { 350, 400 }, 60, 3, WHITE);

}
