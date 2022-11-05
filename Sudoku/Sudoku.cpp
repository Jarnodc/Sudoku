// De Cooman Jarno - 2022
#include "pch.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SudokuBoard.h"

int main()
{

	SudokuBoard* pBoard{new SudokuBoard()};
	pBoard->Generate();

	delete pBoard;
	pBoard = nullptr;

	_CrtDumpMemoryLeaks();
}
