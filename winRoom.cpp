#include "winRoom.h"

WinRoom::WinRoom(const char* backgroundPath, const char* fontPath) :exitButton("Graphics/exit_button.png", { 300, 600 }, 0.24)
{
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
}

WinRoom::~WinRoom()
{
	UnloadTexture(background);
	UnloadFont(font);
}

void WinRoom::Draw()
{
	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "Labyrinth of Echoes: Shards of The Unknown", { 90, 300 }, 40, 3, WHITE);
	DrawTextEx(font, "YOU WON!", { 350, 400 }, 50, 3, WHITE);
	exitButton.DrawButton();

}
bool WinRoom::HandleClickExit()
{
	return exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}
void WinRoom::HandleHover()
{
	exitButton.isHover(GetMousePosition());

}