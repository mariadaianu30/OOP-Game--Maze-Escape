#include "enemy.h"

Enemy::Enemy(int startX, int startY, Texture2D* sharedTex)
{
	position.x = startX;
	position.y = startY;
	tex = sharedTex;
}

bool Enemy::inBounds(int x, int y)
{
	return (x >= 1 && x < cellcount - 1 && y >= 5 && y < cellcount - 1);
}
void Enemy::Update(const std::vector<std::vector<int>>& map, std::mt19937& rng)
{
	if (++frame % step != 0)
		return;
	static const int dx[4] = { 1, -1, 0, 0 };
	static const int dy[4] = { 0, 0, 1, -1 };

	std::uniform_int_distribution<int> dirDist(0, 3);

	int dir = dirDist(rng);
	int newx = position.x + dx[dir];
	int newy = position.y + dy[dir];

	if (newy < 6 || newy >= (int)map.size() - 1 || newx < 2 || newx >= (int)map[0].size() || !(inBounds(newx, newy)))
		return;
	if (map[newy][newx] != 0 || !(inBounds(newx, newy))) return;

	position.x = newx;
	position.y = newy;
}


void Enemy::Draw(float cellSize) const
{

	float scale = 1.7f;
	float px = position.x * cellSize + cellSize / 2.0f;
	float py = position.y * cellSize + cellSize / 2.0f;
	float size = cellSize * scale;

	Rectangle src = { 0, 0,(float)tex->width, (float)tex->height };
	Rectangle dest = { px, py, size, size };
	Vector2   org = { size / 2.0f, size / 2.0f };

	DrawTexturePro(*tex, src, dest, org, 0.0f, WHITE);
}
