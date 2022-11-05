#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Col final
{
public:
	Col(const size_t cols = 1);
	~Col();

	Col(const Col& other) = delete;
	Col(Col&& other) noexcept = delete;
	Col& operator=(const Col& other) = delete;
	Col& operator=(Col&& other) noexcept = delete;

	T operator[](size_t col);
	const T operator[](size_t col) const;

	size_t Width() const { return m_Cols.size(); }

	void Print() const;

	void Fill(const T& value);
private:
	std::vector<T> m_Cols;
};

template <typename T>
Col<T>::Col(const size_t cols)
{
	m_Cols.resize(cols);
}

template <typename T>
Col<T>::~Col()
{
	m_Cols.clear();
}

template <typename T>
T Col<T>::operator[](size_t col)
{
	if (col >= m_Cols.size())
		col = m_Cols.size() - 1;
	return m_Cols[col];
}

template <typename T>
const T Col<T>::operator[](size_t col) const
{
	if (col >= m_Cols.size())
		col = m_Cols.size() - 1;
	return m_Cols[col];
}

template <typename T>
void Col<T>::Print() const
{
	for (size_t col = 0; col < m_Cols.size(); ++col)
	{
		std::cout << m_Cols[col];
		if (col != m_Cols - 1)
			std::cout << ", ";
	}
}

template <typename T>
void Col<T>::Fill(const T& value)
{
	for (size_t col = 0; col < m_Cols.size(); ++col)
	{
		m_Cols[col] = value;
	}
}

template<typename P>
class SaveMatrix final
{
public:
	SaveMatrix(const size_t rows = 1, const size_t cols = 1);
	~SaveMatrix();

	SaveMatrix(const SaveMatrix& other) = delete;
	SaveMatrix(SaveMatrix&& other) noexcept = delete;
	SaveMatrix& operator=(const SaveMatrix& other) = delete;
	SaveMatrix& operator=(SaveMatrix&& other) noexcept = delete;

	Col<P>& operator[](size_t row);
	const Col<P>& operator[](size_t row) const;

	size_t Width() const { return m_Grid[0].Width(); }
	size_t Height() const { return m_Grid.size(); }

	void Print() const;

	void Fill(const P& value);

private:

	std::vector<Col<P>*> m_Grid;
};

template <typename P>
SaveMatrix<P>::SaveMatrix(const size_t rows, const size_t cols)
{
	m_Grid.resize(rows);
	for (size_t row = 0; row < rows; ++row)
	{
		m_Grid[row] = new Col<P>(cols);
	}
}

template <typename P>
SaveMatrix<P>::~SaveMatrix()
{
	for (size_t row = 0; row < m_Grid.size(); ++row)
	{
		delete m_Grid[row];
		m_Grid[row] = nullptr;
	}
}

template <typename P>
Col<P>& SaveMatrix<P>::operator[](size_t row)
{
	if (row >= m_Grid.size())
		row = m_Grid.size() - 1;
	return m_Grid[row];
}

template <typename P>
const Col<P>& SaveMatrix<P>::operator[](size_t row) const
{
	if (row >= m_Grid.size())
		row = m_Grid.size() - 1;
	return m_Grid[row];
}

template <typename P>
void SaveMatrix<P>::Print() const
{
	std::cout << std::endl;
	for (size_t row = 0; row < m_Grid.size(); ++row)
	{
		m_Grid[row].Print();
		std::cout << std::endl;
	}
}

template <typename P>
void SaveMatrix<P>::Fill(const P& value)
{
	for (size_t row = 0; row < m_Grid.size(); ++row)
	{
		m_Grid[row].Fill(value);
	}
}
