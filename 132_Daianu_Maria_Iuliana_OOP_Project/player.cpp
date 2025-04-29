#include "player.h"


Player::Player(int col, int row, Diamond* d) :diamondSystem(d)
{

	texture = safeLoadTexture("Graphics/player.png");
	position.x = col;
	position.y = row;
	diamondCount = 0;
	diamondsCollected.resize(35, std::vector<int>(35, 0));

}
Player::~Player()
{
	UnloadTexture(texture);
}

void Player::DrawObject()
{

	const float scale = 3.3f;


	const float px = position.x * cellsize + cellsize / 2.0f;
	const float py = position.y * cellsize + cellsize / 2.0f;

	const float size = cellsize * scale;

	Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle dest = { px, py, size, size };
	Vector2   origin = { size / 2.0f, size / 2.0f };

	DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);



}

void Player::UpdateObject(const std::vector < std::vector<int>>& maze)
{
	///calculate te next position based on the keyPressed
	int dCol = 0, dRow = 0;
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
		dRow = -1;

	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
		dRow = 1;

	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
		dCol = -1;

	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
		dCol = 1;

	if (dCol == 0 && dRow == 0) return;
	int newCol = position.x + dCol;
	int newRow = position.y + dRow;

	bool inBounds = newCol >= 0 && newCol < cellcount && newRow >= 0 && newRow < cellcount;

	if (inBounds && maze[newCol][newRow] != 1)
	{
		position.x = newCol;
		position.y = newRow;
	}
	if (inBounds && maze[newRow][newCol] == 2 && diamondsCollected[newRow][newCol] == 0)
	{
		diamondCount++;
		diamondsCollected[newRow][newCol] = 1;//we mark the diamond as collected
		diamondSystem->CollectAt(newCol, newRow);	///we want to delete the diamond we just had a collision with

	}
}


bool Player::hasWon(const LabyrinthRoom& room, const Diamond& d) const
{
	bool atExit = room.isExitCell(position.x, position.y);
	bool allTaken = (diamondCount == d.getTotal());
	return atExit && allTaken;
}