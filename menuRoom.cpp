#include "menuRoom.h"

MenuRoom::MenuRoom(const char* backgroundPath, const char* playButtonPath, const char* exitButtonPath, const char* infoButtonPath, const char* fontPath, const char* inputPath)
	: playButton(playButtonPath, { 330,500 }, 0.23), exitButton(exitButtonPath, { 345, 670 }, 0.2), infoButton(infoButtonPath, { 750, 30 }, 0.25)
{
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
	inputBackground = safeLoadTexture(inputPath);
	letters = 0;
	focusText = false;
	exit = false;
	warnTimer = 0.0f;
	inputBox = { 250,400, 400,120 };
	playerName[0] = '\0'; // Initialize the playerName to an empty string
	showInstructions = false;
	keys = safeLoadTexture("Graphics/keys.png");
	arrows = safeLoadTexture("Graphics/arrows.png");
}

MenuRoom::~MenuRoom()
{
	UnloadTexture(background);
	playButton.~Button();
	exitButton.~Button();
	UnloadFont(font);
	UnloadTexture(inputBackground);
}

void MenuRoom::Draw()
{

	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "Labyrinth of Echoes: Shards of The Unknown", { 90, 200 }, 40, 3, WHITE);
	playButton.DrawButton();
	exitButton.DrawButton();
	infoButton.DrawButton();
	DrawTextEx(font, "Enter the player name:", { 280, 350 }, 34, 3, RAYWHITE);
	Rectangle src = { 0, 0, (float)inputBackground.width, (float)inputBackground.height };
	Vector2 origin = { 0,0 };
	DrawTexturePro(inputBackground, src, inputBox, origin, 0.0f, WHITE);
	DrawText(playerName, inputBox.x + 95, inputBox.y + 45, 30, WHITE);
	if (warnTimer > 0.0f)
	{
		unsigned char alpha = (unsigned char)(255 * (warnTimer / WARN_DURATION));
		DrawTextEx(font, "Please enter the player name!",
			{ 260,520 }, 30, 3, RED);
	}
	if (showInstructions)
	{
		DrawRectangle(0, 0, 900, 900, Fade(BLACK, 0.9f));
		DrawTextEx(font, "How to play:", { 350, 130 }, 40, 3, WHITE);
		DrawTextEx(font, "- Use arrow keys or A-W-S-D keys to move", { 100, 210 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "- Avoid traps and find the exit in every room.", { 100, 260 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "- Collect all the diamonds in the maze and find ", { 100, 300 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "your way to the exit to be able to escape.", { 120, 330 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "-But it's not over. Find the diamond in one of the wicked chests.", { 100, 380 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "-Stay away from the enemies and don't step on any obstacle.", { 100, 440 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "-Stepping on an obstacle will cost you 10 seconds of your time.", { 100, 500 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "-Crossing paths with an enemy will kill you.", { 100, 550 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "-Be careful! You only have 3 lives! Or you can buy more!", { 100, 600 }, 28, 2, RAYWHITE);
		DrawTextEx(font, "Press [BACKSPACE] to go back", { 100,800 }, 20, 2, GRAY);
		Rectangle source1 = { 0, 0, (float)keys.width, (float)keys.height };
		Rectangle dest1 = { 250, 650, 150, 120 };
		Vector2 origin = { 0, 0 };
		DrawTexturePro(keys, source1, dest1, origin, 0.0f, WHITE);


		Rectangle source2 = { 0, 0, (float)arrows.width, (float)arrows.height };
		Rectangle dest2 = { 500, 650, 150, 120 };
		DrawTexturePro(arrows, source2, dest2, origin, 0.0f, WHITE);
	}

}


void MenuRoom::HandleInput()
{
	///handles user input to complete the playername char array

	Vector2 mousePos = GetMousePosition();
	bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	if (mousePressed) {
		focusText = CheckCollisionPointRec(mousePos, inputBox);
	}


	///gets the keypressed when the mouse hovers over the inputBox
	if (focusText)
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letters < 9))
			{
				///adds the key pressed in the array
				playerName[letters++] = (char)key;
				playerName[letters] = '\0';
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE) && letters > 0)
		{
			///deletes last character of the array
			--letters;
			playerName[letters] = '\0';
		}
	}
	if (showInstructions && IsKeyPressed(KEY_BACKSPACE)) {
		showInstructions = false;
		return;
	}


}

void MenuRoom::HandleMouseHover(Vector2 mousePos)
{
	playButton.isHover(mousePos);
	exitButton.isHover(mousePos);
	infoButton.isHover(mousePos);
}

void MenuRoom::HandleMouseClick(Vector2 mousePos)
{
	if (playButton.isPressed(mousePos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
	{
		///if the player name array is empty after user input, catch the exception
		try {
			validatePlayerName();
			startGame = true;///if the name is correct the game can start
		}
		catch (const NameMissingException& e)
		{
			triggerWarning(e.what());
		}

	}

	if (exitButton.isPressed(mousePos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
	{
		exit = true;
		///exists the windows
	}
	if (infoButton.isPressed(mousePos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
		showInstructions = true;
	}
}

bool MenuRoom::shouldExit()
{
	return exit;
}
bool MenuRoom::StartGame()
{
	return startGame;
}

void MenuRoom::validatePlayerName() const
{
	if (letters <= 3)
		throw NameMissingException();
}
