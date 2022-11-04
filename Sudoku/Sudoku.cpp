// De Cooman Jarno - 2022
#include "pch.h"
#include "Matrix.h"

int main()
{
	Matrix<int> matrix{ 2,2 };
	matrix.Print();
	std::cout << matrix[2][2];
	matrix.Print();
}
