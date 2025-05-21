#include "GameManager.h"

GameManager::GameManager() :myLab(),
myMenu("Graphics/background.jpg", "Graphics/play_button.png", "Graphics/exit_button.png", "Graphics/font.ttf", "Graphics/inputbox.png"),
myDiamond(myLab.getRoomLayout()),
myCoin(myLab.getRoomLayout()),
myLoseRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myWinRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myPlayerRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myChestRoom(),
myChest(myChestRoom.getRoomLayout()),
myObstacle(myChestRoom.getRoomLayout())
{
	myLab.Load("Graphics/dirt1.png", "Graphics/bush.png", "Graphics/font.ttf");
	myChestRoom.Load("Graphics/dirt1.png", "Graphics/bush.png", "Graphics/font.ttf");
	myDiamond.Load();
	myCoin.Load();
	myChest.Load();
	myObstacle.Load();
}

GameManager::~GameManager()
{
	CloseWindow();
}


void GameManager::UpdateGame() {
	switch (currentScreen) {
	case GameScreen::MENU:
		HandleMenu();
		break;
	case GameScreen::PLAYER:
		HandlePlayerSelect();
		break;
	case GameScreen::MAZE:
		HandleMaze();
		break;
	case GameScreen::TREASURE:
		HandleTreasure();
		break;
	case GameScreen::WIN:
		HandleWin();
		break;
	case GameScreen::LOSE:
		HandleLose();
		break;
	}
}
void GameManager::DrawGame()
{
	switch (currentScreen)
	{
	case GameScreen::MENU:
		myMenu.Draw();
		break;
	case GameScreen::PLAYER:
		myPlayerRoom.Draw();
		break;
	case GameScreen::MAZE:
		myLab.Draw();
		myDiamond.DrawObject();
		myCoin.DrawObject();
		myPlayer->DrawObject();
		DrawText(TextFormat("Diamonds: %d / %d", myPlayer->getDiamondCount(), myDiamond.getTotal()), 600, 60, 25, RAYWHITE);
		DrawText(TextFormat("Time: %.0f", TIME_LIMIT - playTime), 750, 20, 25, RAYWHITE);
		DrawText(TextFormat("Coins:%d", myPlayer->getCoin()), 370, 60, 25, RAYWHITE);
		DrawText(TextFormat("Player Name:  %s", myMenu.getPlayerName()), 40, 60, 25, RAYWHITE);

		for (int i = 0; i < myPlayer->getLives(); ++i)
		{
			Rectangle src = { 0, 0, static_cast<float>(heart.width), static_cast<float>(heart.height) };
			Rectangle dest = { (35 - i) * 20, 7, 50, 50 };
			DrawTexturePro(heart, src, dest, { 0, 0 }, 0.0f, WHITE);
		}
		break;
	case GameScreen::TREASURE:
		myChestRoom.Draw();
		myPlayer->DrawObject();
		myChest.DrawObject();
		myObstacle.DrawObject();
		DrawText(TextFormat("Player Name:  %s", myMenu.getPlayerName()), 40, 60, 25, RAYWHITE);

		for (int i = 0; i < myPlayer->getLives(); ++i)
		{
			Rectangle src = { 0, 0, static_cast<float>(heart.width), static_cast<float>(heart.height) };
			Rectangle dest = { (35 - i) * 20, 7, 50, 50 };
			DrawTexturePro(heart, src, dest, { 0, 0 }, 0.0f, WHITE);
		}
		DrawText(TextFormat("Time: %.0f", std::ceil(chestTimeLeft)), 750, 20, 25, RAYWHITE);
		break;
	case GameScreen::LOSE:
		myLoseRoom.Draw();
		DrawText(TextFormat("You have %d hearts left!", myPlayer->getLives()), 280, 350, 30, RAYWHITE);
		DrawText(TextFormat("Coins:%d", myPlayer->getCoin()), 570, 60, 25, RAYWHITE);
		for (int i = 0; i < myPlayer->getLives(); ++i)
		{
			Rectangle src = { 0, 0, static_cast<float>(heart.width), static_cast<float>(heart.height) };
			Rectangle dest = { (i + 7) * 52, 400, 70, 70 };
			DrawTexturePro(heart, src, dest, { 0, 0 }, 0.0f, WHITE);
		}
		break;
	case GameScreen::WIN:
		myWinRoom.Draw();
		break;
	}
}

void GameManager::HandleMenu()
{
	myMenu.HandleMouseHover(GetMousePosition());
	myMenu.HandleMouseClick(GetMousePosition());
	myMenu.HandleInput(); // handle input for the menu
	myMenu.getPlayerName(); // get the player name from the menu
	myMenu.Update();

	if (myMenu.shouldExit())
		wantExit = true;
	if (myMenu.StartGame())
	{
		currentScreen = GameScreen::PLAYER;
		lastScreen = GameScreen::MENU;
	}
}
void GameManager::HandlePlayerSelect()
{
	myPlayerRoom.HandleClick();
	myPlayerRoom.HandleStart();
	myPlayerRoom.HandleHover();
	myPlayerRoom.Update();
	if (myPlayerRoom.startGame())
	{
		currentScreen = GameScreen::MAZE;
		myPlayer = new Player(1, 5, myPlayerRoom.getCharacter(), &myDiamond, &myCoin, &myChest, &myObstacle, 3, 100, chestTimeLeft);
	}
}

void GameManager::HandleLose()
{
	mazeActive = false;

	lastScreen = GameScreen::MAZE;
	myLoseRoom.HandleHover();

	if (myLoseRoom.HandleClickReplay() && !(myPlayer->lifeLost()))
	{

		ResetGame();

	}
	if (myLoseRoom.HandleClickBuy() && myPlayer->getLives() <= 3 && myPlayer->getCoin() >= 40)
	{
		ResetGame();
		myPlayer->buyLife();
	}
	if (myLoseRoom.HandleClickExit())
	{
		wantExit = true;
	}

}

void GameManager::HandleWin()
{
	myWinRoom.HandleHover();
	if (myWinRoom.HandleClickExit())
	{
		wantExit = true;
	}
}
void GameManager::HandleMaze()
{
	///we use the boolean variable mazeActive for setting the timer only for the maze
	mazeActive = true;
	if (mazeActive)
		playTime += GetFrameTime(); // update the play time
	myPlayer->UpdateObject(myLab.getRoomLayout()); // update the labyrinth room

	///handling the win of the player by stopping the timer and setting the currentscreen to the win room
	if (myPlayer->hasWon(myLab, myDiamond))
	{
		delete myPlayer;
		myPlayer = nullptr;
		finished = true;
		currentScreen = GameScreen::TREASURE;
		mazeActive = false;

	}
	if (playTime >= TIME_LIMIT && !finished)
	{
		currentScreen = GameScreen::TREASURE;
		lastScreen = GameScreen::TREASURE;
		ResetGame();
		myPlayer->loseLife();

	}


}
void GameManager::HandleTreasure() {
	chestTimeLeft = std::max(0.f, chestTimeLeft - GetFrameTime());
	myPlayer->UpdateObject(myChestRoom.getRoomLayout());
	myChestRoom.Update(myPlayer);
	if (chestTimeLeft <= 0.f || myPlayer->lifeLost())
	{
		currentScreen = GameScreen::LOSE;
	}
}

void GameManager::ResetGame()
{
	playTime = 0.f;
	finished = false;
	mazeActive = false;
	currentScreen = lastScreen;

	myLab.Regenerate();
	myDiamond = Diamond(myLab.getRoomLayout());
	myCoin = Coin(myLab.getRoomLayout());
	myDiamond.Load();
	myCoin.Load();
	myChestRoom.Regenerate();
	myChest = Chest(myChestRoom.getRoomLayout());
	myObstacle = Obstacle(myChestRoom.getRoomLayout());
	myChest.Load();
	myObstacle.Load();

	int oldLives = myPlayer->getLives();
	int oldCoins = myPlayer->getCoin();
	delete myPlayer;
	chestTimeLeft = CHEST_LIMIT;
	myPlayer = new Player(1, 5, myPlayerRoom.getCharacter(), &myDiamond, &myCoin, &myChest, &myObstacle, oldLives, oldCoins, chestTimeLeft);
}