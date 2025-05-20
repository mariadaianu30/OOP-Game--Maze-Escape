#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<raylib.h>


class Button
{
private:
	Texture2D buttonTexture;
	Vector2 position;
	bool isHovered = false; // Tracks if the button is currently hovered
	Texture2D originalTexture; // Stores the original texture
	bool originalTextureSaved = false; // Tracks if the original texture is saved
public:
	Button(const char* imagePath, Vector2 imagePosition, float scale);			///constructor holding 3 parameters including the path where is the image we want to upload, the position represented by a Vector2 type of struct and a scale that helps us resize the button
	~Button();
	void DrawButton();											///creates the button
	bool isPressed(Vector2 mousePose, bool mousePressed);		///checks if the button is pressed which allows us to action based on the user choice
	void isHover(Vector2 mousePos);
};