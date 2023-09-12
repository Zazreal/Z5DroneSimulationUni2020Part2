#pragma once

#include <iostream>
#include <vector>
#include "Matrix.hh"
#include "Vector.hh"
#ifndef HH_SYSTEMOFLINEAREQUATIONS
#define HH_SYSTEMOFLINEAREQUATIONS


template<typename type>
class SystemOfLinearEquations
{
private:
	Matrix<type,3> Mmatrix;
	Vector<type,3> result;
public:
	SystemOfLinearEquations<type>();
	inline SystemOfLinearEquations<type>(Matrix<type,3> mat) : Mmatrix{ mat } {};
	void MatrixInput(Matrix<type,3> mat);
	void Gauss();
	Vector<type, 3> Result() const;
	friend std::ostream &operator<<(std::ostream &stream, const SystemOfLinearEquations &system)
	{
		const unsigned int ms = system.Mmatrix.size();
		const unsigned int vs = system.Mmatrix[0].size();
		for (unsigned int i = 0; i < ms; ++i)
		{
			std::cout << "| ";
			for (unsigned int k = 0; k < vs; ++k)
			{
				if (k != ms)
					std::cout << system.Mmatrix[i][k] << " ";
				else if (k == ms)
				{
					if (i == (ms / 2))
						std::cout << "| x_" << i + 1 << " | = |" << system.Mmatrix[i][k] << " |";
					else std::cout << "| x_" << i + 1 << " |   |" << system.Mmatrix[i][k] << " |";
				}
			}
			std::cout << std::endl;
		}
		return stream;
	}

	friend std::istream &operator>>(std::istream &stream, SystemOfLinearEquations &system)
	{
		std::cout << "Please input the matrix of equations." << std::endl;
		std::cin >> system.Mmatrix;
		return stream;
	}
};

template<typename type>
SystemOfLinearEquations<type>::SystemOfLinearEquations(){}

template<typename type>
void SystemOfLinearEquations<type>::MatrixInput(Matrix<type,3> mat)
{
	//uzywa domyslnego copy constructor
	this->Mmatrix = mat;
}

template<typename type>
void SystemOfLinearEquations<type>::Gauss()
{
	int ms = this->Mmatrix.size();
	Matrix<type,3> matrix = this->Mmatrix;
	type det = matrix.DeterminantP();
	if (det == 0)
	{
		std::cout << "Determinant == 0, no solutions";
	}
	std::vector<type> GResult(ms);
	try {
		for (int i = ms - 1; i >= 0; --i) {
			GResult[i] = matrix[i][ms] / matrix[i][i];
			for (int k = i - 1; k >= 0; k--) {
				matrix[k][ms] = matrix[k][ms] - (matrix[k][i] * GResult[i]);
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	this->result = GResult;
}

template<typename type>
Vector<type,3> SystemOfLinearEquations<type>::Result() const
{
	return this->result;
}
#endif // !HH_SYSTEMOFLINEAREQUATIONS