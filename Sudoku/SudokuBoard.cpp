#include "pch.h"
#include "SudokuBoard.h"

SudokuBoard::SudokuBoard(const size_t boardSize)
	:m_Grid(new int*[boardSize])
{
}
