#include "chestRoom.h"

ChestRoom::ChestRoom()
{
	roomLayout.resize(35, std::vector<int>(35, 0));		///initializing the maze with walls
	rng.seed(static_cast<unsigned int>(time(0)));		///seed the generator
	generateLayout();
}
const std::vector <std::vector<int>> ChestRoom::getRoomLayout()
{

	return roomLayout;		///get function to access the roomLayout resulted from the generateLayout function call

};
void ChestRoom::generateLayout() {
	for (int i = 0; i < cellCount - 1; i++)
		for (int j = 0; j < cellCount; j++)
			roomLayout[i][j] = 0;
	generateChests(10);
}

void ChestRoom::Draw()
{
	DrawTexture(background, 0, 0, WHITE);
}
void ChestRoom::generateChests(int chestCount)
{
	std::vector<cell> freeCells;
	for (int row = 0; row < cellCount; ++row)
		for (int col = 5; col < cellCount; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });


	std::shuffle(freeCells.begin(), freeCells.end(), rng);
	const size_t wantChest = static_cast<size_t>(chestCount);

	const size_t haveChests = std::min(wantChest, freeCells.size());

	chests.assign(freeCells.begin(), freeCells.begin() + haveChests);

	for (auto& ch : chests)
		roomLayout[ch.x][ch.y] = 5;
}
void ChestRoom::generateObstacles(int obstacleCount)
{
	std::vector<cell> freeCells;
	for (int row = 0; row < cellCount; ++row)
		for (int col = 5; col < cellCount; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });


	std::shuffle(freeCells.begin(), freeCells.end(), rng);
	const size_t wantChest = static_cast<size_t>(obstacleCount);

	const size_t haveObstacles = std::min(wantChest, freeCells.size());

	obstacles.assign(freeCells.begin(), freeCells.begin() + haveObstacles);

	for (auto& o : obstacles)
		roomLayout[o.x][o.y] = 6;
}