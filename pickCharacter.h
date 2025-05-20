#pragma once
#include <iostream>
#include <exception>
#include "gameException.h"


class PickCharacterException : public GameException {
public:
	PickCharacterException() : GameException("Character is missing!") {}
};

