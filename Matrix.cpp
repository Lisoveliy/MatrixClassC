#include <vector>
#include <iostream>

class Matrix {
private:
	int degree;
public:
	int getDegree()
	{
		return degree;
	}
	void setDegree(int degree)
	{
		this->degree = degree;
	}
private:
	double** element;
public:
	double** getElements()
	{
		return element;
	}
	void setElements(double** elements)
	{
		this->element = elements;
	}
public:
	Matrix()
	{
		this->degree = 3;
		this->element = new double* [3] {
			new double[3] {0, 0, 0},
			new double[3] {0, 0, 0},
			new double[3] {0, 0, 0}
		};
	}
	Matrix(int degree, double** element) {
		this->degree = degree;
		this->element = element;
	}
	Matrix(Matrix* copy)
	{
		this->degree = copy->degree;
		this->element = copy->element;
	}
	 
	void view()
	{
		for (int i = 0; i < degree; i++)
		{
			for (int i2 = 0; i2 < degree; i2++)
			{
				std::cout << element[i][i2] << " ";
			}
			std::cout << std::endl;
		}
	}
	//Find Det for matrix
	double det()
	{
		int row = 0;
		double det = 0;
		//Left to right
		while (row < degree)
		{
			double _det = 1;
			for (int i = 0; i < degree; i++)
			{
				int offset = row;
				if (i + offset >= degree)
				{
					offset -= degree;
				}
				_det *= element[i + offset][i];
			}
			det += _det;
			row++;
		}
		//right to left
		while (row > 0)
		{
			double _det = 1;
			for (int i2 = 0, i = degree - 1; i >= 0; i--, i2++)
			{
				int offset = row - degree;
				if (i + offset < 0)
				{
					offset += degree;
				}
				double el = element[i + offset][i2];
				_det *= el;
			}
			det -= _det;
			row--;
		}
		return det;
	}
};