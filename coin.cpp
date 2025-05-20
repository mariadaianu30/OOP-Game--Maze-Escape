#include "coin.h"

Coin::Coin(const std::vector<std::vector<int>>& maze)
{
	for (int i = 0; i < cellcount; i++)
		for (int j = 0; j < cellcount; j++)

			if (maze[j][i] == 4)
				coins.push_back({ i,j });
	totalCoins = (int)coins.size();
}

Coin::~Coin()
{
	UnloadTexture(texture);
}
void Coin::Load()
{
	texture = safeLoadTexture("Graphics/coin.png");
}
void Coin::DrawObject()
{
	const float scale = 1.0f;
	for (const auto& coin : coins)
	{
		position.x = coin.x;
		position.y = coin.y;


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
void Coin::UpdateObject(const std::vector<std::vector<int>>& maze) {};
void Coin::CollectCoinAt(int col, int row)
{
	coins.erase(std::remove_if(coins.begin(), coins.end(), [=](Cell& c) { return c.x == col && c.y == row; }), coins.end());
}