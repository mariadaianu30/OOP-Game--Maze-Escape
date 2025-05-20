#pragma once  
#include <iostream>  
#include <cstring>  
#include <vector>
#include <raylib.h>  

class Object
{
protected:
	struct Cell { int x, y; };
	Texture2D texture;
	Vector2 position;
	float scale;
	static const int cellsize = 25;
	static const int cellcount = 35;
	static const int screenwidth = cellsize * cellcount;
	static const int screenheight = cellsize * cellcount;
	Font fontObject;

public:
	Object();
	virtual ~Object();
	virtual void UpdateObject(const std::vector < std::vector<int>>& maze);
	virtual void DrawObject();
	virtual void RandomGenerateObject() {};

};