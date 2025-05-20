#include "labyrinthRoom.h"



LabyrinthRoom::LabyrinthRoom()
{

	roomLayout.resize(35, std::vector<int>(35, 1));		///initializing the maze with walls
	rng.seed(static_cast<unsigned int>(time(0)));		///seed the generator
	generateLayout();
	spawnLoot(10, 10);
	sealCeiling();
};

LabyrinthRoom::~LabyrinthRoom()
{
	UnloadTexture(background);		///unloading the textures
	UnloadTexture(wallTexture);
	UnloadFont(font);
	for (auto& diamond : diamonds)
	{
		roomLayout[diamond.x][diamond.y] = 0;			///unloading the diamonds
	}

	roomLayout.clear();
	diamonds.clear();
	coins.clear();
	rng.seed(static_cast<unsigned int>(time(0)));			///resetting the seed
};
void LabyrinthRoom::generateLayout()
{
	int count = 5;
	for (int i = cellCount - 3; i < cellCount - 1; i++)
		for (int j = cellCount - 3; j < cellCount - 1; j++)
			roomLayout[i][j] = 3;			///initializing the exit  with 3s, i choose to initialize a whole 2x2 square to be sure that whatever the generation of the maze is, the player can exit the maze

	for (int i = 0; i < cellCount; i++)
	{
		for (int j = 0; j < 4; j++)

			roomLayout[i][j] = 0;

	}

	generateMaze(1, 5);						///we call the generate maze function


}

bool LabyrinthRoom::inRange(int x, int y)
{
	return (x >= 1 && x < cellCount - 1 &&
		y >= 5 && y < cellCount - 1);
}
void LabyrinthRoom::generateMaze(int x, int y)
{
	///At first we consider that every cell is a wall, meaning that every cell is already visited(1)
	/// We create a directions vector of pairs consisting of two integers, which represent the numbers that have to be added to the current coordinates so that we can reach a neighbour
	/// We do this for each call of the function generateMaze




	roomLayout[x][y] = 0; ///We mark the cell as empty, meaning that it is not a wall
	std::vector < std::pair<int, int>>directions;

	///adding each pair of coordinates for each neighbour
	directions.push_back({ 0,1 });
	directions.push_back({ 1,0 });
	directions.push_back({ 0,-1 });
	directions.push_back({ -1,0 });


	///We shuffle the vector of directions to make sure we pick a random neighbour
	std::shuffle(directions.begin(), directions.end(), rng);

	for (auto& direction : directions)			///we select a neighbour at a time until we find one that can be visited
	{
		int	newX = x + direction.first * 2;		///we move to the cell next to the neighbour
		int newY = y + direction.second * 2;

		if (inRange(newX, newY) && roomLayout[newX][newY] == 1)
		{
			roomLayout[x + direction.first][y + direction.second] = 0; ///we mark the cell between x and newX as 0, meaning it is not a wall, we basically calculated the middle cell between the two cells
			generateMaze(newX, newY);////we call the function recursively
		}
	}
};
const std::vector <std::vector<int>> LabyrinthRoom::getRoomLayout()
{

	return roomLayout;		///get function to access the roomLayout resulted from the generateLayout function call

};


void LabyrinthRoom::Draw()
{

	DrawTexture(background, 0, 0, WHITE);
	const std::vector<std::vector<int>>& layout = getRoomLayout();

	for (int i = 0; i < cellCount; i++)
	{

		for (int j = 0; j < cellCount; j++)
			if (layout[i][j] == 1)
				DrawTexture(wallTexture, i * cellSize, j * cellSize, WHITE);		///we draw the wall texture choosen on each cell marked with 1

	}


}


void LabyrinthRoom::spawnLoot(int diamondCount, int coinCount)
{

	std::vector<cell> freeCells;
	for (int row = 0; row < cellCount; ++row)
		for (int col = 5; col < cellCount; ++col)
			if (roomLayout[row][col] == 0)
				freeCells.push_back({ col,row });


	std::shuffle(freeCells.begin(), freeCells.end(), rng);

	const size_t wantDiam = static_cast<size_t>(diamondCount);
	const size_t wantCoin = static_cast<size_t>(coinCount);

	const size_t haveDiam = std::min(wantDiam, freeCells.size());
	const size_t haveCoin = std::min(wantCoin, freeCells.size() - haveDiam);


	diamonds.assign(freeCells.begin(), freeCells.begin() + haveDiam);

	coins.assign(freeCells.begin() + haveDiam, freeCells.begin() + haveDiam + haveCoin);

	for (auto& d : diamonds)
		roomLayout[d.x][d.y] = 2;

	for (auto& c : coins)
		roomLayout[c.x][c.y] = 4;

}



void LabyrinthRoom::Update()
{
	///timer for error handling
	if (warnTimer > 0.0f)
	{
		warnTimer -= GetFrameTime();
		if (warnTimer < 0.0f)
			warnTimer = 0.0f;
	}
}
bool LabyrinthRoom::isExitCell(int x, int y) const
{
	return roomLayout[x][y] == 3;		///checks if we reached the exit
}

void LabyrinthRoom::Regenerate()
{

	roomLayout.assign(35, std::vector<int>(35, 1));
	diamonds.clear();
	coins.clear();
	rng.seed(static_cast<unsigned int>(time(0)));
	generateLayout();
	spawnLoot(10, 10);
	sealCeiling();



}
inline void LabyrinthRoom::sealCeiling()
{
	for (int x = 0; x < cellCount; ++x)
		roomLayout[x][4] = 1;   // sau roomLayout[4][x] dacă ai axe inversate
}
