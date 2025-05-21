#include "Obstacle.h"

Obstacle::Obstacle(const std::vector<std::vector<int>>& maze)
{
	for (int i = 0; i < cellcount; i++)
		for (int j = 0; j < cellcount; j++)

			if (maze[j][i] == 6)
				obstacles.push_back({ i,j });
	totalObstacles = (int)obstacles.size();

	texIdx.resize(obstacles.size());
}

Obstacle::~Obstacle()
{
	UnloadTexture(texture);
}
void Obstacle::Load()
{
	const char* files[] = {
		"Graphics/obstacle.png",
		"Graphics/bush.png",
	};
	for (const char* p : files)
		textures.push_back(safeLoadTexture(p));


	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, (int)textures.size() - 1);
	for (int& idx : texIdx)
		idx = dist(rng);
}
void Obstacle::DrawObject()
{
	const float scale = 1.2f;
	for (size_t i = 0; i < obstacles.size(); ++i)
	{
		const Cell& c = obstacles[i];
		texture = textures[texIdx[i]];

		float px = c.x * cellsize + cellsize / 2.0f;
		float py = c.y * cellsize + cellsize / 2.0f;
		float size = cellsize * scale;

		Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
		Rectangle dest = { px, py, size, size };
		Vector2   org = { size / 2.0f, size / 2.0f };

		DrawTexturePro(texture, src, dest, org, 0.0f, WHITE);
	}
}

