#include "Obstacle.h"

Obstacle::Obstacle(const std::vector<std::vector<int>>& maze)
{
	for (int i = 0; i < cellcount; i++)
		for (int j = 0; j < cellcount; j++)

			if (maze[j][i] == 6)
				obstacles.push_back({ i,j });
	totalObstacles = (int)obstacles.size();
}

Obstacle::~Obstacle()
{
	UnloadTexture(texture);
}
void Obstacle::Load()
{
	texture = safeLoadTexture("Graphics/Obstacle.png");
}
void Obstacle::DrawObject()
{
	const float scale = 1.0f;
	for (const auto& Obstacle : obstacles)
	{
		position.x = Obstacle.x;
		position.y = Obstacle.y;


		const float px = position.x * cellsize + cellsize / 2.0f;
		const float py = position.y * cellsize + cellsize / 2.0f;

		const float size = cellsize * scale;

		///the DrawTexturePro method ensures that the object is centered correctly in it's cell


		Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };		///the src rectangle is based on the initial dimensions of the texture
		Rectangle dest = { px, py, size, size };
		Vector2   origin = { size / 2.0f, size / 2.0f };

		DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);

	}
}
