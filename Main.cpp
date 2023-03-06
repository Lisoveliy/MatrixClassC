#include <iostream>
#include "matrix.cpp"

int main()
{
	double** elements = new double*[4]{
		new double[4]{3, 11, 5, 3},
		new double[4]{3, 2, 8, 5},
		new double[4]{10, 9, 0, 10},
		new double[4]{0, 10, 4, 3}
	};
	Matrix matrix = new Matrix(4, elements);
	matrix.View();
	std::cout << std::endl;
	matrix.Transponse().View();
	std::cout << std::endl;
	Matrix matrixInversed = new Matrix(matrix);
	matrixInversed.Inverse();
	std::cout << std::endl;
	matrixInversed.View();
	std::cout << std::endl;
	matrix.View();
}