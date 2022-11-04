#pragma once
class SudokuBoard final
{
public:
	SudokuBoard(const size_t boardSize);
	~SudokuBoard() = default;

	SudokuBoard(const SudokuBoard& other) = delete;
	SudokuBoard(SudokuBoard&& other) noexcept = delete;
	SudokuBoard& operator=(const SudokuBoard& other) = delete;
	SudokuBoard& operator=(SudokuBoard&& other) noexcept = delete;

private:
	int** m_Grid;
};

