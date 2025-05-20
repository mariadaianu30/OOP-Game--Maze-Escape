#include "button.h"

Button::Button(const char* imagePath, Vector2 imagePosition, float scale)
{

	///to help the flow of rendering, we work with textures, not with images
	///but for the start, we will upload the image for our button as an image so that we cam resize it, then we insert it as a texture type of object
	Image imageButton = LoadImage(imagePath);		///loads the image
	int initialWidth = imageButton.width;
	int initialHeight = imageButton.height;

	int newHeight = static_cast<int>(initialHeight * scale);		///calculating the new height and width of the element
	int newWidth = static_cast<int>(initialWidth * scale);			///we use static_cast to ensure the result in converted to int , given the float scale

	if (newHeight > 0 && newWidth > 0)
		ImageResize(&imageButton, newWidth, newHeight);					///calling the ImageResize method of raylib.h library
	buttonTexture = LoadTextureFromImage(imageButton);
	UnloadImage(imageButton);										///after we are done working with the image we just resized, we unload it so that we can clear up some memory from the GPU

	position = imagePosition;
};

Button:: ~Button()
{

	UnloadTexture(buttonTexture);///unloading the texture of the button after we are done working with the first page of the game
	position = { -1, -1 };
	isHovered = false;
	originalTextureSaved = false;

};
void Button::DrawButton()
{
	DrawTexture(buttonTexture, position.x, position.y, WHITE);
};


bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
	Rectangle rect = { position.x, position.y,static_cast<float>(buttonTexture.width),static_cast<float>(buttonTexture.height) };			///marking the rectangle that the button imaginary creates
	if (CheckCollisionPointRec(mousePos, rect) && mousePressed)																				///we check if the mouse is pressed in the rectangle declared
		return true;
	else
		return false;
};

void Button::isHover(Vector2 mousePos)
{
	///create a visual animation when the button is hovered over

	Rectangle rect = { position.x, position.y, static_cast<float>(buttonTexture.width), static_cast<float>(buttonTexture.height) };

	if (CheckCollisionPointRec(mousePos, rect))
	{
		if (!isHovered)
		{
			if (!originalTextureSaved)
			{
				originalTexture = buttonTexture; // Save the original texture
				originalTextureSaved = true;
			}

			Image image = LoadImageFromTexture(buttonTexture);
			int width = static_cast<int>(image.width * 0.95);
			int height = static_cast<int>(image.height * 0.95);
			ImageResize(&image, width, height);
			buttonTexture = LoadTextureFromImage(image);
			UnloadImage(image);
			isHovered = true;
		}
	}
	else
	{
		if (isHovered)
		{
			buttonTexture = originalTexture; // Restore the original texture
			isHovered = false;
		}
	}
}