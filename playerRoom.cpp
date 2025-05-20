#include "playerRoom.h"

PlayerRoom::PlayerRoom(const char* backgroundPath, const char* fontPath) :playerGirl({ 100, 350, 300, 300 }, "Graphics/girlframe1.png", "Graphics/girl.png"), playerBoy({ 500, 350, 300, 300 }, "Graphics/boyframe.png", "Graphics/boy.png"), playButton("Graphics/play_button.png", { 340,650 }, 0.2f)
{
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
}

void PlayerRoom::Draw()
{
	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "Labyrinth of Echoes: Shards of The Unknown", { 90, 220 }, 40, 3, WHITE);

	playerGirl.DrawObject();
	playerBoy.DrawObject();
	if (showThanksGirl)
	{
		Rectangle src = { 0, 0, (float)thanks.width, (float)thanks.height };
		Rectangle dest = { 300, 200, 300, 400 };
		DrawTexturePro(thanks, src, dest, { 0, 0 }, 0.0f, WHITE);
	}

	if (showThanksBoy)
	{
		Rectangle src = { 0, 0, (float)thanks.width, (float)thanks.height };
		Rectangle dest = { 600, 200, 300, 400 };
		DrawTexturePro(thanks, src, dest, { 0, 0 }, 0.0f, WHITE);
	}
	playButton.DrawButton();
	DrawTextEx(font, "CHOOSE YOUR PLAYER! ", { 270, 300 }, 43, 3, WHITE);
	if (warnTimer > 0.0f)
	{
		unsigned char alpha = (unsigned char)(255 * (warnTimer / WARN_DURATION));
		DrawTextEx(font, "Please choose your character!",
			{ 260,650 }, 30, 3, RED);
	}
}
const char* PlayerRoom::HandleClick()
{
	if (playerGirl.clickedObject(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))

	{
		character = playerGirl.getCharacterPath();
		showThanksGirl = true;
		showThanksBoy = false;
	}
	else if (playerBoy.clickedObject(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))

	{
		character = playerBoy.getCharacterPath();
		showThanksBoy = true;
		showThanksGirl = false;
	}
	return character;
}

void PlayerRoom::HandleStart()
{
	if (playButton.isPressed(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
	{
		try {
			checkIfPicked();
			start = true;///if the name is correct the game can start
		}
		catch (const PickCharacterException& e)
		{
			triggerWarning(e.what());
		}

	}
}
void PlayerRoom::HandleHover()
{
	playButton.isHover(GetMousePosition());
}
void PlayerRoom::checkIfPicked()
{
	if (!(showThanksGirl || showThanksBoy))
		throw PickCharacterException();
}

bool PlayerRoom::startGame()
{
	return start;
}