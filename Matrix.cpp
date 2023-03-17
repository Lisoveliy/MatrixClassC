#include <vector>
#include <iostream>
#include <math.h>
#include <string>

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
	Matrix()
	{
		this->degree = 3;
		this->element = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			this->element[i] = new double[degree];
			for (int i2 = 0; i2 < degree; i2++)
			{
				this->element[i][i2] = 0;
			}
		}
		setElements(new double* [3] {
			new double[3] {0, 0, 0},
				new double[3] {0, 0, 0},
				new double[3] {0, 0, 0}
			});
	}
	Matrix(int degree, double** element) {
		this->degree = degree;
		double** newelement = new double* [degree];
		for (int i = 0; i < degree; i++)


		{
			newelement[i] = new double[degree];
			for (int i2 = 0; i2 < degree; i2++)
			{
				newelement[i][i2] = element[i][i2];
			}
		}
		this->element = newelement;
	}
	Matrix(Matrix* copy)
	{
		this->degree = copy->degree;
		double** newelement = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			newelement[i] = new double[degree];
			for (int i2 = 0; i2 < degree; i2++)
			{
				newelement[i][i2] = copy->element[i][i2];
			}
		}
		this->element = newelement;
	}
	//Matrix(std::wstring matrix)
	//{
	//	//found degree
	//	int degree = 0;
	//	for (int ptr = 0; ptr < matrix.length(); ptr++)
	//	{
	//		if (matrix[ptr] == ' ')
	//		{
	//			degree++;
	//		}
	//		if (matrix[ptr] == '\n')
	//		{
	//			degree++;
	//			break;
	//		}
	//	}
	//	//get elements
	//	double** prepareelements = new double*[degree];
	//	this->degree = degree;
	//	for (int row = 0; row < degree; row++)
	//	{
	//		prepareelements[row] = new double[degree];
	//		int column = 0;
	//		std::wstring input;
	//		for (int ptr = 0; matrix[ptr+(row*degree)] != '\n'; ptr++) {
	//			if(matrix[ptr+(row * degree)] != ' ' && matrix[ptr+(row * degree)] != '\n')
	//			{
	//				input += matrix[ptr+ (row * degree)];
	//			}
	//			else
	//			{
	//				prepareelements[row][column] = stoi(input);
	//				column++;
	//				input = L"";
	//			}
	//		}
	//	}
	//	this->element = prepareelements;
	//}
	~Matrix()
	{
		for (int i = 0; i < degree; i++)
		{
			delete[] element[i];
		}
	}

	void View()
	{
		for (int i = 0; i < degree; i++)
		{
			for (int i2 = 0; i2 < degree; i2++)
			{
				std::wcout << getElements()[i][i2] << " ";
			}
			std::wcout << std::endl;
		}
	}
	Matrix Transponse()
	{
		double** transposedElement = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			transposedElement[i] = new double[degree];
		}
		for (int i = 0; i < degree; i++)
		{
			for (int i2 = 0; i2 < degree; i2++)
			{
				int reverseIndex = abs(degree - 1 - i);
				transposedElement[reverseIndex][i2] = element[i2][reverseIndex];
			}
		}
		return new Matrix(degree, transposedElement);
	}
	//I died here
	void Inverse()
	{
		double** A = element;
		int N = degree;
		double temp;

		double** E = new double* [N];

		for (int i = 0; i < N; i++)
			E[i] = new double[N];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				E[i][j] = 0.0;

				if (i == j)
					E[i][j] = 1.0;
			}

		for (int k = 0; k < N; k++)
		{
			temp = A[k][k];

			for (int j = 0; j < N; j++)
			{
				A[k][j] /= temp;
				E[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				A[i][j] = E[i][j];

		for (int i = 0; i < N; i++)
			delete[] E[i];
		delete[] E;
	}
	//Find Det for matrix
	double Det()
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
	//AX=B? Я не пон. что она хочет
	Matrix Change(int i, int j)
	{
		Matrix* changed = new Matrix(this);
		double* icolumn = changed->getElements()[i - 1];
		double* jrow = new double[changed->degree];
		for (int iter = 0; iter < changed->degree; iter++)
		{
			jrow[iter] = changed->getElements()[iter][i - 1];
		}
		changed->element[i - 1] = jrow;
		for (int iter = 0; iter < changed->degree; iter++)
		{
			changed->element[iter][i - 1] = icolumn[iter];
		}
		return new Matrix(changed);
	}
	bool operator == (const Matrix &x)
	{
		if (this->degree != x.degree)
		{
			return false;
		}
		for (int i = 0; i < this->degree; i++)
		{
			for (int i2 = 0; i < this->degree; i2++)
			{
				if (this->element[i][i2] != x.element[i][i2])
					return false;
			}
		}
		return true;
	}
};