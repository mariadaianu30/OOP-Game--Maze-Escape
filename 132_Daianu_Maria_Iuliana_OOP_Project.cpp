///Dăianu Maria-Iuliana
///Grupa 132
/// An Universitar 2024-2025

/*  Instruct?iuni rapide de joc
	1)  Meniu: treci cursorul peste ca?su?a de text, scrie-?i numele ?i apasă Enter.
	2)  Labirint: mi?că-te cu săge?ile ???? sau cu tastele A-W-S-D.
	3)  Adună toate diamantele ?i găse?te ie?irea înainte să expire cele 150 de secunde.
	Succes la evadare!
*/

#include "raylib.h"
#include "resources.h"
#include "fileLoad.h"
#include "GameManager.h"


int main() {

	///we used the try and catch method to ensure the files loaded are valid and not throwing an access violation when running the game

	InitWindow(875, 875, "Dungeon Escape");
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



