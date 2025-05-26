#pragma once
#include <iostream>
#include <functional>
#include <optional>
#include <vector>
#include <string>
#include <algorithm>
#include "object.h"
#include "resources.h"

template<typename T>
class Chest :public Object
{
private:

	struct chestCell
	{
		Cell pos;
		T  chest;
		bool opened = false;
	};
	std::vector < chestCell > chests;
	Texture2D closedChest{};
	Texture2D openedChest{};
	Texture2D coinTex{};
	Texture2D diamondTex{};
public:
	Chest(const std::vector < std::vector<int>>& maze, std::function<T()> lootGen)
	{
		for (int i = 0; i < cellcount; i++)
			for (int j = 0; j < cellcount; j++)

				if (maze[j][i] == 5)
					chests.push_back({ { i, j }, lootGen(), false });


	}

	~Chest()
	{
		UnloadTexture(closedChest);
		UnloadTexture(openedChest);
	}
	void DrawObject() override
	{
		const float scale = 2.0f;
		const float size = cellsize * scale;
		Rectangle srcClosed = { 0,0, (float)closedChest.width, (float)closedChest.height };
		Rectangle srcOpened = { 0,0, (float)openedChest.width, (float)openedChest.height };
		for (const auto& chest : chests)
		{
			const float px = chest.pos.x * cellsize + cellsize / 2.0f;
			const float py = chest.pos.y * cellsize + cellsize / 2.0f;
			Rectangle dest = { px, py, size, size };
			Vector2   origin = { size / 2.0f, size / 2.0f };

			DrawTexturePro(chest.opened ? openedChest : closedChest, chest.opened ? srcOpened : srcClosed, dest, origin, 0.0f, WHITE);


			if (chest.opened)
			{
				Texture2D lootTex = (chest.chest == "coin")
					? coinTex : diamondTex;

				Rectangle srcLoot = { 0, 0,static_cast<float>(lootTex.width),static_cast<float>(lootTex.height) };

				const float lootSize = size * 0.6f;
				Rectangle destLoot = { px, py - size * 0.4f,lootSize, lootSize };
				Vector2 originLoot = { lootSize / 2.f, lootSize / 2.f };

				DrawTexturePro(lootTex, srcLoot, destLoot, originLoot, 0.f, WHITE);
			}
		}
	}
	void Load()
	{
		closedChest = safeLoadTexture("Graphics/chest.png");
		openedChest = safeLoadTexture("Graphics/chest1.png");
		diamondTex = safeLoadTexture("Graphics/diamond.png");
		coinTex = safeLoadTexture("Graphics/coin.png");
	}

	std::optional<T> OpenAt(int col, int row)
	{
		auto it = std::find_if(chests.begin(), chests.end(), [&](const chestCell& c)
			{
				return c.pos.x == col && c.pos.y == row;
			});
		if (it == chests.end() || it->opened)
			return std::nullopt;

		it->opened = true;
		return it->chest;
	}

	int countOpenedChests() const {
		return std::count_if(chests.begin(), chests.end(), [](const chestCell& c) 
			{
			return c.opened;
			}
		);
	}
	int getChestCount() const {
		return chests.size();
	}
};
template<typename T>
std::string getChestProgressText(const Chest<T>& chest) {
	int opened = chest.countOpenedChests();
	int total = chest.getChestCount();
	return std::to_string(opened) + " / " + std::to_string(total);
}