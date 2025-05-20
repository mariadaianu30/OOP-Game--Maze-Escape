#include "loseRoom.h"


LoseRoom::LoseRoom(const char* backgroundPath, const char* fontPath) : replayButton("Graphics/retry_button.png", { 150,600 }, 0.2), exitButton("Graphics/exit_button.png", { 550, 600 }, 0.2), buyButton("Graphics/buy_button.png", { 350, 500 }, 0.35)
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
	exitButton.~Button();
	buyButton.~Button();
	UnloadFont(font);
}

void LoseRoom::Draw()
{
	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "You lost!", { 350, 200 }, 60, 3, WHITE);
	replayButton.DrawButton();
	exitButton.DrawButton();
	buyButton.DrawButton();

}
void LoseRoom::HandleHover()
{
	replayButton.isHover(GetMousePosition());
	exitButton.isHover(GetMousePosition());
	buyButton.isHover(GetMousePosition());
}

bool LoseRoom::HandleClickReplay()
{
	return replayButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}
bool LoseRoom::HandleClickBuy()
{
	return buyButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

bool LoseRoom::HandleClickExit()
{
	return exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}