#include "scoreManager.h"

void ScoreManager::evaluateLabyrinthScore(const Player& player, const LabyrinthRoom& room, const Diamond& diamonds) {
	if (!player.hasWonMaze(room, diamonds)) return;		///if the player has not won the maze, we don't evaluate the score

	float time = player.getRemainingTime();

	if (time > 60) labyrinthScore = 100;				///if the player has more than 60 seconds left, he gets 100 points
	else if (time > 30) labyrinthScore = 70;			///if the player has more than 30 seconds left, he gets 70 points
	else if (time > 10) labyrinthScore = 50;			///if the player has more than 30 seconds left, he gets 70 points
	else labyrinthScore = 40;
}

void ScoreManager::evaluateChestRoomScore(const Player& player, const ChestRoom& room)
///we evaluate the score only if the player has won the treasure room
{
	if (!player.hasWonTreasure(room)) return;

	float time = player.getRemainingTime();
	///the same logic as before
	if (time > 60) chestRoomScore = 100;
	else if (time > 30) chestRoomScore = 70;
	else chestRoomScore = 50;
}

int ScoreManager::getTotalScore() const {
	return labyrinthScore + chestRoomScore;		///we return the total score, which is the sum of the labyrinth score and the chest room score
}
