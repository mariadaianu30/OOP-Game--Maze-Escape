#include "chestRoom.h"

ChestRoom::ChestRoom()
{
	roomLayout.resize(35, std::vector<int>(35, 0));		///initializing the maze with walls
	rng.seed(static_cast<unsigned int>(time(0)));		///seed the generator
	enemyTex = safeLoadTexture(enemyPath);
	generateLayout();
}
ChestRoom::~ChestRoom()
{
	UnloadTexture(enemyTex);
}
const std::vector <std::vector<int>> ChestRoom::getRoomLayout()
{

	return roomLayout;		///get function to access the roomLayout resulted from the generateLayout function call

};
void ChestRoom::generateLayout() {
	for (int i = 0; i < cellCount - 1; i++)
		for (int j = 0; j < cellCount; j++)
			roomLayout[i][j] = 0;			///initialize the roomLayout with 0s, meaning free cells
	for (int i = cellCount - 3; i < cellCount - 1; i++)
		for (int j = cellCount - 3; j < cellCount - 1; j++)
			roomLayout[i][j] = 3;		///initialize the last 2 rows and columns with 3s, marking the exit cells
	generateChests(7, 5);
	generateObstacles(50, 2);
	generateEnemies(7);
}

void ChestRoom::Draw()
{
	DrawTexture(background, 0, 0, WHITE);
	for (auto& e : enemies)
	{
		e.Draw(cellSize);
	}
}
void ChestRoom::generateChests(int chestCount, int minDist)		///generate chests in the room
{
	chests.clear();
	std::vector<cell> freeCells;
	for (int row = 2; row < cellCount; ++row)
		for (int col = 5; col < cellCount - 1; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });			///push all the free cells in a vector, so we can randomly select from them


	std::shuffle(freeCells.begin(), freeCells.end(), rng);		///shuffle the free cells to randomize the chest placement

	const int minDist2 = minDist * minDist;						///calculate the minimum area in between the chests, so they don't overlap
	for (const auto& ch : freeCells) {
		if (chests.size() >= chestCount) break;

		bool ok = true;
		for (const auto& placed : chests)
			if (dist2(ch, placed) < minDist2)
			{
				ok = false; break;
			}

		if (!ok) continue;

		chests.push_back(ch);			///if the chest is placed correctly, we push it in the chests vector
		roomLayout[ch.x][ch.y] = 5;		///mark the cell as occupied by a chest
	}


}
void ChestRoom::generateObstacles(int obstacleCount, int minDist)
{
	std::vector<cell> freeCells;
	for (int row = 2; row < cellCount; ++row)
		for (int col = 5; col < cellCount - 1; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });			///the same logic as in the generateChests function, we push all the free cells in a vector, so we can randomly select from them


	std::shuffle(freeCells.begin(), freeCells.end(), rng);

	obstacles.clear();

	const int minDist2 = minDist * minDist;
	for (const auto& o : freeCells) {
		if (obstacles.size() >= obstacleCount) break;

		bool ok = true;
		for (const auto& placed : obstacles)			///check if the obstacle can be placed in the current cell
			if (dist2(o, placed) < minDist2)

			{
				ok = false; break;
			}


		if (!ok) continue;

		obstacles.push_back(o);		///if the obstacle is placed correctly, we push it in the obstacles vector
		roomLayout[o.x][o.y] = 6;		///mark the cell as occupied by an obstacle
	}
}

void ChestRoom::generateEnemies(int enemyCount)
{
	std::vector<cell> free;
	for (int row = 5; row < cellCount - 1; ++row)
		for (int col = 5; col < cellCount - 1; ++col)

			free.push_back({ col, row });

	std::shuffle(free.begin(), free.end(), rng);

	enemies.clear();
	for (int i = 0; i < enemyCount && i < (int)free.size(); ++i)		///we load the enemies in the room, if there are enough free cells
		enemies.emplace_back(free[i].x, free[i].y, &enemyTex);
}

void ChestRoom::Update(Player* player)
{
	for (auto& e : enemies)

		e.Update(roomLayout, rng);
	enemyCollision(player);


}

void ChestRoom::enemyCollision(Player* player)
{
	for (auto& e : enemies)
	{
		if (e.getXenemy() == player->getXplayer() && e.getYenemy() == player->getYplayer())		///if the player collides with an enemy , it loses all his lives
		{
			player->loseLife();
			break;
		}

	}
}
void ChestRoom::Regenerate()		///reset the room to the initial state, reinitialize the chests, enemies and obstacles
{

	roomLayout.assign(35, std::vector<int>(35, 0));
	enemies.clear();
	obstacles.clear();
	rng.seed(static_cast<unsigned int>(time(0)));
	generateLayout();
	generateChests(7, 5);
	generateEnemies(7);
	generateObstacles(70, 2);



}