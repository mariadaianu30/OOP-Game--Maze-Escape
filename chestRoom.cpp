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
			roomLayout[i][j] = 0;
	generateChests(7, 5);
	generateObstacles(70, 2);
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
void ChestRoom::generateChests(int chestCount, int minDist)
{
	std::vector<cell> freeCells;
	for (int row = 1; row < cellCount; ++row)
		for (int col = 5; col < cellCount - 1; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });


	std::shuffle(freeCells.begin(), freeCells.end(), rng);

	chests.clear();

	const int minDist2 = minDist * minDist;
	for (const auto& ch : freeCells) {
		if (chests.size() >= chestCount) break;

		bool ok = true;
		for (const auto& placed : chests)
			if (dist2(ch, placed) < minDist2) {
				ok = false; break;
			}

		if (!ok) continue;

		chests.push_back(ch);
		roomLayout[ch.x][ch.y] = 5;
	}


}
void ChestRoom::generateObstacles(int obstacleCount, int minDist)
{
	std::vector<cell> freeCells;
	for (int row = 1; row < cellCount; ++row)
		for (int col = 5; col < cellCount - 1; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });


	std::shuffle(freeCells.begin(), freeCells.end(), rng);

	obstacles.clear();

	const int minDist2 = minDist * minDist;
	for (const auto& o : freeCells) {
		if (obstacles.size() >= obstacleCount) break;

		bool ok = true;
		for (const auto& placed : obstacles)
			if (dist2(o, placed) < minDist2)

			{
				ok = false; break;
			}


		if (!ok) continue;

		obstacles.push_back(o);
		roomLayout[o.x][o.y] = 6;
	}
}

void ChestRoom::generateEnemies(int enemyCount)
{
	std::vector<cell> free;
	for (int row = 1; row < cellCount; ++row)
		for (int col = 5; col < cellCount - 1; ++col)
			if (roomLayout[row][col] == 0)
				free.push_back({ col, row });

	std::shuffle(free.begin(), free.end(), rng);

	enemies.clear();
	for (int i = 0; i < enemyCount && i < (int)free.size(); ++i)
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
		if (e.getXenemy() == player->getXplayer() && e.getYenemy() == player->getYplayer())
		{
			player->loseLife();
			break;
		}

	}
}
void ChestRoom::Regenerate()
{

	roomLayout.assign(35, std::vector<int>(35, 1));
	enemies.clear();
	obstacles.clear();
	rng.seed(static_cast<unsigned int>(time(0)));
	generateLayout();
	generateChests(7, 5);
	generateEnemies(7);
	generateObstacles(70, 2);



}