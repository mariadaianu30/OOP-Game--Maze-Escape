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
