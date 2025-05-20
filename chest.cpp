#include "Chest.h"

Chest::Chest(const std::vector<std::vector<int>>& maze)
{
	for (int i = 0; i < cellcount; i++)
		for (int j = 0; j < cellcount; j++)

			if (maze[j][i] == 5)
				chests.push_back({ i,j });
	totalChests = (int)chests.size();
}

Chest::~Chest()
{
	UnloadTexture(texture);
}
void Chest::Load()
{
	texture = safeLoadTexture("Graphics/chest.png");
}
void Chest::DrawObject()
{
	const float scale = 2.0f;
	for (const auto& chest : chests)
	{
		position.x = chest.x;
		position.y = chest.y;


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
void Chest::UpdateObject(const std::vector<std::vector<int>>& maze) {};
void Chest::CollectChestAt(int col, int row)
{
	chests.erase(std::remove_if(chests.begin(), chests.end(), [=](Cell& c) { return c.x == col && c.y == row; }), chests.end());
}