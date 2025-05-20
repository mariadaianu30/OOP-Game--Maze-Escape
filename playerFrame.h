#pragma once
#include <iostream>
#include "object.h"
#include "resources.h"
class PlayerFrame : public Object
{
private:
	const char* framePath;
	const char* characterPath;
	Rectangle frameBox; // Add this declaration to match the constructor parameter.  

public:
	PlayerFrame(Rectangle frameBox, const char* framePath, const char* characterPath);
	void DrawObject() override;
	bool clickedObject(Vector2 mousePosition, bool clicked);
	const char* getCharacterPath() { return characterPath; };
};

