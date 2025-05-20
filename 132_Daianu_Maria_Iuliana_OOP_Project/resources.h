#pragma once
#include "gameException.h"
#include "fileLoad.h"
#include "raylib.h"

inline Texture2D safeLoadTexture(const char* fileName)
{
	Texture2D texture = LoadTexture(fileName);
	if (texture.id == 0)

		throw FileLoadException();

	return texture;
}

inline Image safeLoadImage(const char* fileName)
{
	Image image = LoadImage(fileName);
	if (image.data == nullptr)
		throw FileLoadException();
	return image;
}

inline Font safeLoadFont(const char* fileName)
{
	Font font = LoadFont(fileName);
	if (font.baseSize == 0)
		throw FileLoadException();
	return font;
}