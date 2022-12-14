#pragma once
#include "SaveMatrix.h"

class SudokuBoard final
{
public:
	SudokuBoard(const size_t boardSize, const size_t amountBlocks);
	SudokuBoard();
	~SudokuBoard() = default;

	SudokuBoard(const SudokuBoard& other) = delete;
	SudokuBoard(SudokuBoard&& other) noexcept = delete;
	SudokuBoard& operator=(const SudokuBoard& other) = delete;
	SudokuBoard& operator=(SudokuBoard&& other) noexcept = delete;

	void Generate();
	int FirstStartCell(const SaveMatrix<int>& board, size_t& col, size_t& row) const;

	void SetBoard(const SaveMatrix<int>& board);
private:
	std::vector<int> GetAvailableNumbers(const size_t row, const size_t col) const;
	std::vector<int> GetHorizontalNumbers(const size_t row) const;
	std::vector<int> GeVertictalNumbers(const size_t col) const;
	std::vector<int> GetBlockNumbers(const size_t row, const size_t col) const;

	bool Contains(const std::vector<int>& list, const int value) const;

	bool Solve(size_t row, size_t col);

	bool IsSolvable() const;

	SaveMatrix<int> m_pBoard;
	const size_t m_Size,m_AmountBlocks;
};

