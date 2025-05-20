#pragma once  
#include <iostream>  
#include <cstring>  
#include <vector>
#include <raylib.h>  

class Object
{
protected:
	Texture2D texture;
	Vector2 position;
	float scale;
	int cellsize = 25;
	int cellcount = 35;
	int screenwidth = cellsize * cellcount;
	int screenheight = cellsize * cellcount;
	Font fontObject;

public:
	Object();
	~Object();
	virtual void UpdateObject(const std::vector < std::vector<int>>& maze);
	virtual void DrawObject();
	virtual void RandomGenerateObject() {};

};