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

void SudokuBoard::Generate()
{
	srand(static_cast<unsigned>(time(NULL)));
	m_pBoard.Fill(0);
	const size_t blockSize{ m_Size / m_AmountBlocks };

	for (size_t i = 0; i < m_AmountBlocks; i++)
	{
		for (size_t y = 0; y < blockSize; ++y)
		{
			for (size_t x = 0; x < blockSize; ++x)
			{
				const auto availableNumbers{ GetAvailableNumbers(x + blockSize * i,y + blockSize * i) };
				const auto idx{ rand() % availableNumbers.size() };
				m_pBoard[x + blockSize * i][y + blockSize * i] = availableNumbers[idx];
			}
		}
	}
	Solve(0, 0);
	m_pBoard.Print();


}

std::vector<int> SudokuBoard::GetAvailableNumbers(const size_t row, const size_t col) const
{
	std::vector<int> availableNumbers{};

	const std::vector<int> nrHor{ GetHorizontalNumbers(col)}, nrVer{ GeVertictalNumbers(row)}, nrBlock{ GetBlockNumbers(col,row)};

	for (int i = 0; i < m_Size; ++i)
	{
		const int value{ i + 1 };

		//if contains in one the list, check other number
		if(Contains(nrHor,value))
			continue;
		if(Contains(nrVer,value))
			continue;
		if(Contains(nrBlock,value))
			continue;
		//else add to available
		availableNumbers.emplace_back(value);
	}

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
			if(m_pBoard[y * blockSize + i][x * blockSize + j] != 0)
			{
				availableNumbers.emplace_back(m_pBoard[y * blockSize + i][x * blockSize + j]);
			}
		}
	}

	return availableNumbers;
}

bool SudokuBoard::Contains(const std::vector<int>& list, const int value) const
{
	for (size_t i = 0; i < list.size(); ++i)
	{
		if (list[i] == value)
			return true;
	}
	return false;
}

bool SudokuBoard::Solve(size_t row, size_t col)
{
	if (row == m_Size - 1 && col == m_Size)
		return true;

	if(col == m_Size)
	{
		++row;
		col = 0;
	}

	if (m_pBoard[row][col] != 0)
		return Solve(row, col + 1);

	for (int nr = 1; nr <= m_Size; ++nr)
	{
		if(Contains(GetAvailableNumbers(row,col),nr))
		{
			m_pBoard[row][col] = nr;

			if (Solve(row, col + 1))
				return true;

			m_pBoard[row][col] = 0;
		}

	}
	return false;
}
