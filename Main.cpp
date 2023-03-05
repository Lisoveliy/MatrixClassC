#include <iostream>
#include "matrix.cpp"

int main()
{
	double** elements = new double*[3]{
		new double[3]{3, 11, 5},
		new double[3]{3, 2, 8},
		new double[3]{10, 9, 0}
	};
	Matrix matrix = new Matrix(3, elements);
	matrix.View();
	std::cout << std::endl;
	matrix.Transponse().View();
}