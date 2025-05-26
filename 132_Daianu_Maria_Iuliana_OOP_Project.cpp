///Dăianu Maria-Iuliana
///Grupa 132
/// An Universitar 2024-2025

#include "raylib.h"
#include "resources.h"
#include "fileLoad.h"
#include "GameManager.h"


int main() {

	///we used the try and catch method to ensure the files loaded are valid and not throwing an access violation when running the game

	InitWindow(875, 875, "The Last Treasure");
	SetTargetFPS(60);
	try
	{
		GameManager game;
		while (!WindowShouldClose() && game.getExit() == false)
		{
			game.UpdateGame();
			BeginDrawing();
			ClearBackground(BLACK);
			game.DrawGame();
			EndDrawing();
		}
		CloseWindow();
	}
	catch (FileLoadException& e)
	{
		///the load file exception is handled by creating a window that outputs a significant message
		InitWindow(640, 200, "Critical Error");
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(e.what(), 20, 80, 20, RED);
		EndDrawing();
		WaitTime(4.0);
		CloseWindow();
	}

}



