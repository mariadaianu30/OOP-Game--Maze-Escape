#pragma once
#include <iostream>
#include "gameException.h"

class FileLoadException : public GameException {
public:
	FileLoadException() : GameException("File could not be loaded!") {}
};
