#include "winRoom.h"

WinRoom::WinRoom(const char* backgroundPath, const char* fontPath) :exitButton("Graphics/exit_button.png", { 350, 650 }, 0.2)
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
	DrawTextEx(font, "The Last Treasure: Heart of The Gem", { 150, 300 }, 40, 3, WHITE);
	DrawTextEx(font, "YOU WON!", { 350, 420 }, 50, 3, WHITE);
	exitButton.DrawButton();
	Rectangle src = { 0, 0, (float)reward.width, (float)reward.height };
	Rectangle dst = { 350, 500, 200, 200 };
	Vector2 origin = { 0, 0 };
	DrawTexturePro(reward, src, dst, origin, 0.0f, WHITE);

}
bool WinRoom::HandleClickExit()
{
	return exitButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}
void WinRoom::HandleHover()
{
	exitButton.isHover(GetMousePosition());

}
void WinRoom::update(int score) {
	std::string newPath;
	///we update the reward texture based on the score
	if (score >= 140)
		newPath = "Graphics/gold.png";
	else if (score >= 100)
		newPath = "Graphics/silver.png";
	else
		newPath = "Graphics/bronze.png";

	///if the new path is different from the current one, we unload the old texture and load the new one
	///we do this so that we don't keep loading the same texture multiple times, which would waste memory
	if (newPath != currentRewardPath) {
		if (reward.id != 0)
			UnloadTexture(reward);

		reward = safeLoadTexture(newPath.c_str());
		currentRewardPath = newPath;
	}

}

