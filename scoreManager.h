#pragma once
#include "observer.h"
#include "player.h"
#include "labyrinthRoom.h"
#include "chestRoom.h"

class ScoreManager : public Subject {
private:
	int labyrinthScore = 0;
	int chestRoomScore = 0;

public:
	void evaluateLabyrinthScore(const Player& player, const LabyrinthRoom& room, const Diamond& diamonds);
	void evaluateChestRoomScore(const Player& player, const ChestRoom& room);

	int getTotalScore() const;
};
