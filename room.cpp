#include "room.h"

Room::Room()
{
	roomLayout.resize(35, std::vector<int>(35, 1)); // Initialize a 20x20 grid with zeros

	roomCode = 0;
};

Room::Room(const Room& other)
{
	roomName = other.roomName;
	roomCode = other.roomCode;
};

Room::~Room()
{
};

void  Room::generateLayout() {

};

void Room::Draw()
{

}
void Room::Load()
{
};

void Room::triggerWarning(const char* msg)
{
	//  Copy the message (max 49 characters + null terminator)
	strncpy_s(warnMessage, sizeof(warnMessage), msg, _TRUNCATE);

	// Reset the timer; 
	warnTimer = WARN_DURATION;
}

void Room::Update()
{
	if (warnTimer > 0.0f)
	{
		warnTimer -= GetFrameTime();
		if (warnTimer < 0.0f)
			warnTimer = 0.0f;
	}
}
void Room::Load(const char* groundPath, const char* wallPath, const char* fontPath)
{

	///created a load method to ensure all of the files are uploaded correctly
	Image image = safeLoadImage(groundPath);
	ImageResize(&image, windowSize, windowSize);
	background = LoadTextureFromImage(image);
	UnloadImage(image);
	image = safeLoadImage(wallPath);
	ImageResize(&image, cellSize, cellSize);
	wallTexture = LoadTextureFromImage(image);
	SetTextureFilter(wallTexture, TEXTURE_FILTER_POINT);
	UnloadImage(image);
	font = safeLoadFont(fontPath);

}