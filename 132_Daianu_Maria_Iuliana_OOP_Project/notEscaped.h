#pragma once
#include <iostream>
#include <exception>
#include "gameException.h"

class NotEscapedException : public GameException {
public:
	NotEscapedException() : GameException("You have not escaped the labyrinth!") {}
};