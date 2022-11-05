#include "pch.h"
#include "SudokuBoard.h"

SudokuBoard::SudokuBoard(const size_t boardSize, const size_t amountBlocks)
	:m_pBoard(SaveMatrix<int>(boardSize,boardSize)) // square matrix
	,m_Size(boardSize)
	,m_AmountBlocks(amountBlocks)
{
}

SudokuBoard::SudokuBoard()
	:SudokuBoard(9,3)
{
}

void SudokuBoard::Generate(const size_t amountNumbers)
{
	srand(static_cast<unsigned>(time(NULL)));
	m_pBoard.Fill(0);
	for (int i = 0; i < amountNumbers; ++i)
	{
	}
}

std::vector<int> SudokuBoard::GetAvailableNumbers(const size_t row, const size_t col) const
{
	std::vector<int> availableNumbers{};
	for (int i = 0; i < m_Size; ++i)
	{
		availableNumbers.emplace_back(i + 1);
	}

	const std::vector<int> nrHor{ GetHorizontalNumbers(row)}, nrVer{ GeVertictalNumbers(col)}, nrBlock{ GetBlockNumbers(row,col)};



	return availableNumbers;
}

std::vector<int> SudokuBoard::GetHorizontalNumbers(const size_t row) const
{
	std::vector<int> availableNumbers{};
	for (size_t i = 0; i < m_Size; i++)
	{
		if(m_pBoard[i][row] != 0)
		{
			availableNumbers.emplace_back(m_pBoard[i][row]);
		}
	}
	return availableNumbers;
}

std::vector<int> SudokuBoard::GeVertictalNumbers(const size_t col) const
{
	std::vector<int> availableNumbers{};
	for (size_t i = 0; i < m_Size; i++)
	{
		if (m_pBoard[col][i] != 0)
		{
			availableNumbers.emplace_back(m_pBoard[col][i]);
		}
	}
	return availableNumbers;
}

std::vector<int> SudokuBoard::GetBlockNumbers(const size_t row, const size_t col) const
{
	const size_t x{ row / m_AmountBlocks }, y{ col / m_AmountBlocks };

	const size_t blockSize{ m_Size / m_AmountBlocks };


	std::vector<int> availableNumbers{};

	for (size_t j = 0; j < blockSize; ++j)
	{
		for (size_t i = 0; i < blockSize; ++i)
		{
			if(m_pBoard[x * blockSize + i][y * blockSize + j] != 0)
			{
				availableNumbers.emplace_back(m_pBoard[x * blockSize + i][y * blockSize + j]);
			}
		}
	}

	return availableNumbers;
}
