#include "object.h"
Object::Object() :texture{}, position{}, scale(1.0f)
{
	texture = LoadTexture("Graphics/empty.png");
	position.x = 0 * cellsize;
	position.y = 0 * cellsize;
	fontObject = LoadFont("Graphics/font.ttf");
};
Object::~Object()
{
	UnloadTexture(texture);
};
void Object::UpdateObject(const std::vector<std::vector<int>>& maze)
{


};

void Object::DrawObject()
{

};