#include "menuRoom.h"

MenuRoom::MenuRoom(const char* backgroundPath, const char* playButtonPath, const char* exitButtonPath, const char* fontPath)
	: playButton(playButtonPath, { 330,500 }, 0.23), exitButton(exitButtonPath, { 345, 670 }, 0.2)
{
	Image backgroundImg = safeLoadImage(backgroundPath);
	ImageResize(&backgroundImg, windowSize, windowSize);
	background = LoadTextureFromImage(backgroundImg);
	UnloadImage(backgroundImg);
	font = safeLoadFont(fontPath);
	inputBox = { 250,400,400,70 };
	letters = 0;
	focusText = false;
	exit = false;
	warnTimer = 0.0f;
	playerName[0] = '\0'; // Initialize the playerName to an empty string
}

MenuRoom::~MenuRoom()
{
	UnloadTexture(background);
	playButton.~Button();
	exitButton.~Button();
	UnloadFont(font);
}

void MenuRoom::Draw()
{

	ClearBackground(BLACK);
	DrawTexture(background, 0, 0, WHITE);
	DrawTextEx(font, "Labyrinth of Echoes: Shards of The Unknown", { 90, 200 }, 40, 3, WHITE);
	playButton.DrawButton();
	exitButton.DrawButton();
	DrawTextEx(font, "Enter the player name:", { 280, 350 }, 34, 3, RAYWHITE);
	DrawRectangleRec(inputBox, LIGHTGRAY);
	DrawRectangleLinesEx(inputBox, 1.0, DARKBROWN);
	DrawText(playerName, inputBox.x + 8, inputBox.y + 12, 30, DARKBROWN);
	if (warnTimer > 0.0f)
	{
		unsigned char alpha = (unsigned char)(255 * (warnTimer / WARN_DURATION));
		DrawTextEx(font, "Please enter the player name!",
			{ 270,500 }, 30, 3, RED);
	}
}

void MenuRoom::HandleInput()
{
	///handles user input to complete the playername char array
	Vector2 mousePos = GetMousePosition();
	bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

	bool focus = CheckCollisionPointRec(mousePos, inputBox);
	///gets the keypressed when the mouse hovers over the inputBox
	if (focus)
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letters < 15))
			{
				///adds the key pressed in the array
				playerName[letters] = (char)key;
				letters += 1;
				playerName[letters] = '\0';
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE) && letters > 0)
		{
			///deletes last character of the array
			playerName[letters] = '\0';
			letters -= 1;
		}
	}

}

void MenuRoom::HandleMouseHover(Vector2 mousePos)
{
	playButton.isHover(mousePos);
	exitButton.isHover(mousePos);
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
}

bool MenuRoom::shouldExit()
{
	return exit;
}
bool MenuRoom::StartGame()
{
	return startGame;
}

void MenuRoom::Update()
{
	///sets timer for warning

	if (warnTimer > 0.0f)
	{
		warnTimer -= GetFrameTime();
		if (warnTimer < 0.0f)
			warnTimer = 0.0f;
	}
}

void MenuRoom::validatePlayerName() const
{
	if (letters == 0)
		throw NameMissingException();
}
void MenuRoom::triggerWarning(const char* msg)
{
	//  Copy the message (max 49 characters + null terminator)
	strncpy_s(warnMessage, sizeof(warnMessage), msg, _TRUNCATE);

	// Reset the timer; 
	warnTimer = WARN_DURATION;
}