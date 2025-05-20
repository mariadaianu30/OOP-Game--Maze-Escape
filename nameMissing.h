#pragma once
#include <iostream>
#include <exception>
#include "gameException.h"


class NameMissingException : public GameException {
public:
	NameMissingException() : GameException("Player name is missing!") {}
};

