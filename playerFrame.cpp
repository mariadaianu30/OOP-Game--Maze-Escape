#include "playerFrame.h"

PlayerFrame::PlayerFrame(Rectangle frameBox, const char* framePath, const char* characterPath) : frameBox(frameBox), framePath(framePath), characterPath(characterPath)
{
	texture = safeLoadTexture(framePath);

}
void PlayerFrame::DrawObject()
{
	Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
	DrawTexturePro(texture, src, frameBox, { 0,0 }, 0.0f, WHITE);
}

bool PlayerFrame::clickedObject(Vector2 mousePosition, bool clicked)
{
	if (CheckCollisionPointRec(mousePosition, frameBox) && clicked)
		return true;
	else
		return false;
}