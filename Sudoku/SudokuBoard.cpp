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

	int trials{}, amountEmpty{};
	while(trials != 20)
	{
		const size_t x{ rand() % m_Size }, y{ rand() % m_Size };
		if(m_pBoard[x][y] != 0)
		{
			const auto num = m_pBoard[x][y];
			m_pBoard[x][y] = 0;
			
			if (IsSolvable())
			{
				trials = 0;
				++amountEmpty;
			}
			else
			{
				++trials;
				m_pBoard[x][y] = num;
			}
		}
	}

	size_t row, col;
	const int value{ FirstStartCell(m_pBoard,col, row) };
	std::cout << "Start with: " << row << ", " << col << " with value: " << value << std::endl;
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

bool SudokuBoard::IsSolvable() const
{

	SaveMatrix<int> boardCopy{9,3};
	for (int col = 0; col < m_Size; ++col)
	{
		for (int row = 0; row < m_Size; ++row)
		{
			boardCopy[row][col] = m_pBoard[row][col];
		}
	}

	for (int x = 0; x < m_Size; ++x)
	{
		for (int y = 0; y < m_Size; ++y)
		{
			for (int col = 0; col < m_Size; ++col)
			{
				for (int row = 0; row < m_Size; ++row)
				{
					if (boardCopy[row][col] == 0)
					{
						const auto availableNrs{ GetAvailableNumbers(row, col) };
						if (availableNrs.size() == 1)
						{
							boardCopy[row][col] = availableNrs.front();
						}
					}
				}
			}
		}
	}

	for (int col = 0; col < m_Size; ++col)
	{
		for (int row = 0; row < m_Size; ++row)
		{
			if (boardCopy[row][col] == 0)
				return false;
		}
	}
	return true;
}

int SudokuBoard::FirstStartCell(const SaveMatrix<int>& board, size_t& col, size_t& row) const
{
	for (int x = 0; x < m_Size; ++x)
	{
		for (int y = 0; y < m_Size; ++y)
		{
			for (int c = 0; c < m_Size; ++c)
			{
				for (int r = 0; r < m_Size; ++r)
				{
					if (board[r][c] == 0)
					{
						const auto availableNrs{ GetAvailableNumbers(r, c) };
						if (availableNrs.size() == 1)
						{
							col = c;
							row = r;
							return availableNrs.front();
						}
					}
				}
			}
		}
	}
	return 0;
}

void SudokuBoard::SetBoard(const SaveMatrix<int>& board)
{
	
	for (int x = 0; x < m_Size; ++x)
	{
		for (int y = 0; y < m_Size; ++y)
		{
			m_pBoard[x][y] = board[x][y];
		}
	}
}
