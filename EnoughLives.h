#pragma once
#include <iostream>
#include <exception>
#include "gameException.h"


class NotEnoughLives : public GameException {
public:
	NotEnoughLives() : GameException("Player doesn't have any hearts!") {}
};

