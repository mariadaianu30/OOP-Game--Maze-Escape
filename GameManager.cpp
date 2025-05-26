#include "GameManager.h"

///constructor of GameManager class containing the initialization of the rooms, the player and the objects
GameManager::GameManager() :myLab(),
myDiamond(myLab.getRoomLayout()),
myCoin(myLab.getRoomLayout()),
myLoseRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myWinRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myPlayerRoom("Graphics/background.jpg", "Graphics/font.ttf"),
myChestRoom(),
myChest(myChestRoom.getRoomLayout(),
	[oneDiamond = true]() mutable -> std::string {
		if (oneDiamond) { oneDiamond = false; return "diamond"; }		///generate only a diamond in of the chests
		return "coin";
	}),
	myObstacle(myChestRoom.getRoomLayout())

{
	MenuRoom::GetInstance("Graphics/background.jpg", "Graphics/play_button.png", "Graphics/exit_button.png",
		"Graphics/info.png", "Graphics/font.ttf", "Graphics/inputbox.png");

	myLab.Load("Graphics/dirt1.png", "Graphics/bush.png", "Graphics/font.ttf");
	myChestRoom.Load("Graphics/dirt2.png", "Graphics/bush.png", "Graphics/font.ttf");
	myDiamond.Load();
	myCoin.Load();
	myChest.Load();
	myObstacle.Load();
}

GameManager::~GameManager()
{
	CloseWindow();
}


void GameManager::UpdateGame() {		///handle game logic and update the game state based on the current screen
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
void GameManager::DrawGame()  ///draw the game based on the current screen
{
	switch (currentScreen)
	{
	case GameScreen::MENU:
		MenuRoom::GetInstance()->Draw();
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
		DrawText(TextFormat("Player Name:  %s", MenuRoom::GetInstance()->getPlayerName()), 40, 60, 25, RAYWHITE);


		for (int i = 0; i < myPlayer->getLives(); ++i)	///draw the hearts avaliable for the player
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
		DrawText(TextFormat("Coins:%d", myPlayer->getCoin()), 370, 60, 25, RAYWHITE);
		DrawText(TextFormat("Player Name:  %s", MenuRoom::GetInstance()->getPlayerName()), 40, 60, 25, RAYWHITE);

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
		DrawText(TextFormat("Coins:%d", myPlayer->getCoin()), 700, 60, 30, RAYWHITE);
		if (showRetryWarning && retryWarnTimer > 0.0f) {
			DrawText("Not enough lives to retry!", 230, 430, 35, RED);
		}

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

void GameManager::HandleMenu()			///handle the menu screen logic
{
	MenuRoom::GetInstance()->HandleMouseHover(GetMousePosition());   ///we use the singleton pattern to ensure only one instance of MenuRoom exists
	MenuRoom::GetInstance()->HandleMouseClick(GetMousePosition());
	MenuRoom::GetInstance()->HandleInput();
	MenuRoom::GetInstance()->getPlayerName();
	MenuRoom::GetInstance()->Update();

	if (MenuRoom::GetInstance()->shouldExit())
		wantExit = true;

	if (MenuRoom::GetInstance()->StartGame())
	{
		currentScreen = GameScreen::PLAYER;
		lastScreen = GameScreen::MENU;
	}
}
void GameManager::HandlePlayerSelect()		///the player selection screen logic
{
	myPlayerRoom.HandleClick();
	myPlayerRoom.HandleStart();
	myPlayerRoom.HandleHover();
	myPlayerRoom.Update();
	if (myPlayerRoom.startGame())
	{
		currentScreen = GameScreen::MAZE;
		myPlayer = new Player(1, 5, myPlayerRoom.getCharacter(), &myDiamond, &myCoin, &myChest, &myObstacle, 3, 100, chestTimeLeft);	///create the player with the selected character and the objects
	}
}

void GameManager::HandleLose()			///handle the lose screen logic
{
	mazeActive = false;

	lastScreen = GameScreen::MAZE;
	myLoseRoom.HandleHover();

	if (myLoseRoom.HandleClickReplay())	 ///if the player wants to retry the game, we check if he has enough lives
	{

		try {
			if (myPlayer->lifeLost())
				throw NotEnoughLives();	///if the player has no lives left, we throw an exception

			ResetGame();
		}
		catch (const NotEnoughLives& e) {   ///if the player has no lives left, we show a warning
			showRetryWarning = true;
			retryWarnTimer = 3.0f;
		}
	}
	if (myLoseRoom.HandleClickBuy() && myPlayer->getLives() <= 3 && myPlayer->getCoin() >= 40) ///	///if the player wants to buy a life, we check if he has enough coins
	{
		ResetGame();
		myPlayer->buyLife();		///a heart costs 40 coins
	}
	if (myLoseRoom.HandleClickExit())		///if the player wants to exit the game, we set the wantExit variable to true
	{
		wantExit = true;
	}
	if (showRetryWarning) {				///if the player has no lives left, we show a warning for 3 seconds
		retryWarnTimer -= GetFrameTime();
		if (retryWarnTimer <= 0.0f) {
			retryWarnTimer = 0.0f;
			showRetryWarning = false;
		}
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

	///handling the win of the player by stopping the timer and setting the currentscreen to the treasure room
	if (myPlayer->hasWonMaze(myLab, myDiamond))
	{
		int oldLives = myPlayer->getLives();
		int oldCoins = myPlayer->getCoin();
		delete myPlayer;
		chestTimeLeft = CHEST_LIMIT;
		///we reinitialize the player with the new objects and the old lives and coins, and given start position
		myPlayer = new Player(1, 5, myPlayerRoom.getCharacter(), &myDiamond, &myCoin, &myChest, &myObstacle, oldLives, oldCoins, chestTimeLeft);
		finished = true;
		currentScreen = GameScreen::TREASURE;
		mazeActive = false;

	}
	if (playTime >= TIME_LIMIT && !finished)			///if the player has not won the maze in the given time, we set the current screen to lose
	{
		currentScreen = GameScreen::LOSE;
		lastScreen = GameScreen::LOSE;
		ResetGame();
		myPlayer->loseLife();

	}


}
void GameManager::HandleTreasure() {
	chestTimeLeft = std::max(0.f, chestTimeLeft - GetFrameTime());	///update the chest time left and check if the player has won the treasure
	myPlayer->UpdateObject(myChestRoom.getRoomLayout());

	myChestRoom.Update(myPlayer);
	if (myPlayer->hasWonTreasure(myChestRoom))	///if the player finds the diamond, he wins the game
	{

		finished = true;
		currentScreen = GameScreen::WIN;
		lastScreen = GameScreen::WIN;
	}
	if (chestTimeLeft <= 0.f || myPlayer->lifeLost())	///if the player has no time left or loses a life, we set the current screen to lose
	{
		currentScreen = GameScreen::LOSE;
		lastScreen = GameScreen::LOSE;
		ResetGame();
		myPlayer->loseLife();
	}
}

void GameManager::ResetGame()	 ///reset the game to the initial state, reinitialize the player and the objects
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
	myChest = Chest<std::string>(myChestRoom.getRoomLayout(),
		[oneDiamond = true]() mutable -> std::string {
			if (oneDiamond) { oneDiamond = false; return "diamond"; }
			return "coin";
		}),
		myObstacle = Obstacle(myChestRoom.getRoomLayout());
	myChest.Load();
	myObstacle.Load();

	int oldLives = myPlayer->getLives();
	int oldCoins = myPlayer->getCoin();
	delete myPlayer;
	chestTimeLeft = CHEST_LIMIT;
	myPlayer = new Player(1, 5, myPlayerRoom.getCharacter(), &myDiamond, &myCoin, &myChest, &myObstacle, oldLives, oldCoins, chestTimeLeft);
}