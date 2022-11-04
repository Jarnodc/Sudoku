#pragma once
#include <iostream>


template<typename T>
class Matrix
{
public:
	Matrix(const size_t rows = 1, const size_t cols = 1);
	~Matrix() = default;

	Matrix(const Matrix& other) = delete;
	Matrix(Matrix&& other) noexcept = delete;
	Matrix& operator=(const Matrix& other) = delete;
	Matrix& operator=(Matrix&& other) noexcept = delete;

	T* operator[](size_t row);
	const T* operator[](size_t row) const;

	size_t Width() const { return m_Cols; }
	size_t Height() const { return m_Rows; }

	void Print() const;

private:

	T** m_Grid;
	const size_t m_Rows, m_Cols;
};

template<typename T>
inline Matrix<T>::Matrix(const size_t rows, const size_t cols)
	:m_Rows(rows)
	,m_Cols(cols)
{
	m_Grid = new T* [rows];
	for (size_t row = 0; row < m_Rows; ++row)
	{
		m_Grid[row] = new T[cols];
	}
}

template<typename T>
inline T* Matrix<T>::operator[](size_t row)
{
	if (row >= m_Rows)
		row = m_Rows - 1;
	return m_Grid[row];
}

template<typename T>
inline const T* Matrix<T>::operator[](size_t row) const
{
	if (row >= m_Rows)
		row = m_Rows - 1;
	return m_Grid[row];
}

template<typename T>
inline void Matrix<T>::Print() const
{
	std::cout << std::endl;
	for (size_t row = 0; row < m_Rows; ++row)
	{
		for (size_t col = 0; col < m_Cols; ++col)
		{
			std::cout << m_Grid[row][col];
			if (col != m_Cols - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
}
