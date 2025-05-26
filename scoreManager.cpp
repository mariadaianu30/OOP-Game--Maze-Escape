#include "scoreManager.h"

void ScoreManager::evaluateLabyrinthScore(const Player& player, const LabyrinthRoom& room, const Diamond& diamonds) {
	if (!player.hasWonMaze(room, diamonds)) return;

	float time = player.getRemainingTime();

	if (time > 60) labyrinthScore = 100;
	else if (time > 30) labyrinthScore = 70;
	else labyrinthScore = 40;
}

void ScoreManager::evaluateChestRoomScore(const Player& player, const ChestRoom& room) {
	if (!player.hasWonTreasure(room)) return;

	float time = player.getRemainingTime();

	if (time > 60) chestRoomScore = 100;
	else if (time > 30) chestRoomScore = 70;
	else chestRoomScore = 50;
}

int ScoreManager::getTotalScore() const {
	return labyrinthScore + chestRoomScore;
}
