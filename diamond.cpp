#include "diamond.h"

Diamond::Diamond(const std::vector < std::vector<int>>& maze)
{
	scale = 1.0f;

	for (int i = 0; i < cellcount; i++)
		for (int j = 0; j < cellcount; j++)
			if (maze[j][i] == 2)
			{
				diamonds.push_back({ i,j });		///the vector of position for where the diamonds should be inserted
			}
	totalDiamonds = (int)diamonds.size();			///we get the number of diamonds needed to complete the game
}

Diamond::~Diamond()
{
	///we unload the texture of the diamond
	///we call the destructor when the diamond is collected by the player
	UnloadTexture(texture);

}
void Diamond::Load()
{
	texture = safeLoadTexture("Graphics/diamond.png");
}
void Diamond::UpdateObject(const std::vector < std::vector<int>>& maze)
{


}
void Diamond::CollectDiamondAt(int col, int row)
{
	///when we collect a diamond, we want to delete it
	diamonds.erase(std::remove_if(diamonds.begin(), diamonds.end(), [=](Cell& d) { return d.y == row && d.x == col; }), diamonds.end());

	///the std::remove_if method moves the elements of the vector that don't correspond to our criteria to the front of the vector
	///the method doesn't erase the objects that do not correspond , it just moves them to the end of the vector when it's done it's job with it
	/// the lambda function receives each diamond by reference 
	/// if the positions of the diamond iterated match the parameters, we move the diamond to the beggining of the vector and we call the erase function to delete it 
}


void Diamond::DrawObject()
{

	for (const auto& diamond : diamonds)
	{
		position.x = diamond.x;
		position.y = diamond.y;


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



