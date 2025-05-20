///Dãianu Maria-Iuliana
///Grupa 132
/// An Universitar 2024-2025
/*  Instrucțiuni rapide de joc
	1)  Meniu: treci cursorul peste căsuța de text, scrie-ți numele și apasă Enter.
	2)  Labirint: mișcă-te cu săgețile ↑↓←→ sau cu tastele A-W-S-D.
	3)  Adună toate diamantele și găsește ieșirea înainte să expire cele 150 de secunde.
	Succes la evadare!
*/

#include <iostream>
#include<cstring>
#include "raylib.h"
#include "labyrinthRoom.h"
#include "button.h"
#include "menuRoom.h"
#include "room.h"
#include "player.h"
#include "object.h"
#include "diamond.h"
#include "notEscaped.h"
#include "loseRoom.h"
#include "winRoom.h"
#include "fileLoad.h"


int cellsize = 25;
int cellcount = 35;
int screenwidth = cellsize * cellcount;
int screenheight = cellsize * cellcount;
std::string playerName;
const float TIME_LIMIT = 150.f;
float playTime = 0.f;
bool  finished = false;
bool mazeActive = false;
GameScreen currentScreen = GameScreen::MENU;

/// creates a room with a specific layout
int main()
{

	///we used the try and catch method to ensure the files loaded are valid and not throwing an access violation when running the game
	try
	{
		InitWindow(screenheight, screenwidth, "Dungeon Escape");
		SetTargetFPS(60); // sets the target FPS to 60 to ensure that the game runs at a consistent speed on every computer
		////generating the maze info

		LabyrinthRoom myLab = LabyrinthRoom();

		myLab.Load("Graphics/dirt.jpg", "Graphics/bush.png", "Graphics/font.ttf"); // load the textures for the labyrinth room
		MenuRoom myMenu("Graphics/background.jpg", "Graphics/play_button.png", "Graphics/exit_button.png", "Graphics/font.ttf");
		Diamond myDiamond = Diamond(myLab.getRoomLayout());
		Player myPlayer = Player(1, 5, &myDiamond);
		LoseRoom myLoseRoom("Graphics/background.jpg", "Graphics/font.ttf", "Graphics/replay_button.png");
		WinRoom myWinRoom("Graphics/background.jpg", "Graphics/font.ttf", "Graphics/replay_button.png");


		////initializing the game window

		try
		{
			while (!WindowShouldClose() && myMenu.shouldExit() == false) // while the window is open
			{

				if (currentScreen == GameScreen::MENU)
				{
					///instatiate the methods that make out=r menu functional
					myMenu.HandleMouseHover(GetMousePosition());
					myMenu.HandleMouseClick(GetMousePosition());
					myMenu.HandleInput(); // handle input for the menu
					myMenu.getPlayerName(); // get the player name from the menu
					myMenu.Update();

					if (myMenu.StartGame())
					{
						currentScreen = GameScreen::MAZE;
					}
				}
				else if (currentScreen == GameScreen::MAZE)
				{
					///we use the boolean variable mazeActive for setting the timer only for the maze
					mazeActive = true;
					if (mazeActive)
						playTime += GetFrameTime(); // update the play time
					myPlayer.UpdateObject(myLab.getRoomLayout()); // update the labyrinth room

					///handling the win of the player by stopping the timer and setting the currentscreen to the win room
					if (myPlayer.hasWon(myLab, myDiamond))
					{
						finished = true;
						currentScreen = GameScreen::WIN;
						mazeActive = false;

					}
					///if the playtime is over and the player didn't finish the game, the notEscaped exception is thrown
					if (playTime >= TIME_LIMIT && !finished)
						throw NotEscapedException();
				}





				BeginDrawing(); // creates a black canvas
				ClearBackground(BLACK);


				///handling which room to draw based on the room we are currently in
				switch (currentScreen)
				{
				case GameScreen::MENU: myMenu.Draw(); break;
				case GameScreen::MAZE:
					myLab.Draw();
					myDiamond.DrawObject();
					myPlayer.DrawObject();
					DrawText(TextFormat("Diamonds: %d / %d", myPlayer.getDiamondCount(), myDiamond.getTotal()), 20, 20, 28, RAYWHITE);/// printing in our window the number of collected diamonds out of the diamonds the player has to collect
					DrawText(TextFormat("Time: %.0f", TIME_LIMIT - playTime), 20, 60, 28, RAYWHITE);///print time left until the game is over
					break;


				case GameScreen::LOSE:myLoseRoom.Draw(); break;
				case GameScreen::WIN: myWinRoom.Draw(); break;
				}

				EndDrawing(); // draws the canvas


				CloseWindow(); // close the game window
			}
		}
		catch (NotEscapedException& e)
		{
			///the exception is handled by drawing the lose room in the same window
			currentScreen = GameScreen::LOSE;
			mazeActive = false;
			while (WindowShouldClose() == false)
			{
				BeginDrawing();
				myLoseRoom.Draw();
				EndDrawing();
			}
			CloseWindow();


		}
	}

	catch (FileLoadException& e)
	{
		///the load file exception is handled by creating a window that outputs a significant message
		InitWindow(640, 200, "Critical Error");
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(e.what(), 20, 80, 20, RED);   // mesaj din excepþie
		EndDrawing();
		WaitTime(4.0);    // menþine 4 secunde cât sã citeºti
		CloseWindow();
	}
}
