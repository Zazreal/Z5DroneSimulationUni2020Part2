#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
/*
	Klasa zawiera 2D array zrobiona z std::vector
	w ten sposob mozna ja dynamicznie zwiekszac
	i nie potrzebny jest znany rozmiar w trakcie deklaracji.
	Wszystkie metody klasy sluza do obslugi tej macierzy.
 */

#ifndef HH_MATRIX
#define HH_MATRIX



template<typename T>
T string_to_template(std::string str);

template<typename type, int m_size>
class Matrix
{
protected:
	std::vector<std::vector<type>> matrix;
public:
	Matrix();
	Matrix(std::vector<std::vector<type>>& m);
	~Matrix();
	int size() const;
	void PrinMatrix() const;
	void Transposition();
	type Determinant();
	type DeterminantP();
	std::vector<type> Determinant(char a);
	std::vector<std::vector<type>>& GeMatrix();
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(const double other) const;
	std::vector<type> operator[](const unsigned int index) const;
	std::vector<type>& operator[](const unsigned int index);
	void AddEl(std::vector<type> el);
	//Matrix operator!();
	friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
	{
		for (std::vector<type> vector : matrix.matrix)
		{
			stream << " |";
			for (auto element : vector) {
				stream << " " << element;
			}
			stream << " | " << std::endl;;
		}
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, Matrix& matrix)
	{
		//funkcja przetestowana, dziala bez zarzutow
		std::vector<type> temp(0); //tymczasowy wektor do ulatwienia pracy
		std::string element; // potrzebne do pobrania danych
		type input;
		int vecsize = 0;
		bool pass = 0;
		std::cout << "Starting input, enter \"=\" to input last element in row, enter \"stop\" to stop" << std::endl;
		while (true) {										//potrzeba 2 loopy rzeby wypelnic 2D tablice (tutaj vectory)
			while (true)
			{
				std::cout << "Input element: ";
				stream >> element;
				if ("stop" == element) break;
				else if ("=" == element) {						// = sluzy za loop breaker
					std::cout << "Input last element: ";
					stream >> element;
					input = string_to_template<type,m_size>(element);
					temp.emplace_back(input);
					break;
				}
				else
				{
					input = string_to_template<type,m_size>(element);
					temp.emplace_back(input);
				}
			}
			if (pass == false) {							//ten caly kawalek odpowiada za sprawdzanie rozmiaru macierzy
				vecsize = temp.size(); pass = true;
			}
			if (temp.size() != vecsize)
			{
				temp.clear();
				if ("stop" == element) break;
				std::cerr << "Wrong vector size, try again" << std::endl;
				continue;
			}												//tu sie konczy sprawdzanie rozmiaru
			matrix.matrix.emplace_back(temp);				//wrzucam vektor do macierzy
			temp.clear();									//czyszcze wektor do pozniejszego uzytku
			if ("stop" == element) break;
		}
		return stream;
	}
	friend std::ofstream& operator<<(std::ofstream& stream, const Matrix& matrix)
	{
		for(auto vec: matrix)
		{
			for(int i; i<vec.size();++i)
			{
				stream<<vec[i];
			}
			std::cout<<std::endl;
		}
		return stream;
	}
};

template<typename type, int m_size>
Matrix<type, m_size>::Matrix()
{
	std::vector<type> temp(m_size);
	for (int i = 0; i < m_size; ++i)
	{
		this->matrix.emplace_back(temp);
	}
}
template<typename type, int m_size>
Matrix<type,m_size>::Matrix(std::vector<std::vector<type>>& m) : matrix{ m }
{
}

template<typename type, int m_size>
Matrix<type,m_size>::~Matrix()
{
}

template<typename type, int m_size>
int Matrix<type,m_size>::size() const
{
	return this->matrix.size();
}

template<typename type, int m_size>
void Matrix<type,m_size>::AddEl(std::vector<type> el)
{
	int temp = this->matrix.size();
	if(el.size() == temp)
	{
		for(int i = 0;i<temp;++i)
		{
			this->matrix[i].emplace_back(el[i]);
		}
	}
}
template<typename type, int m_size>
void Matrix<type,m_size>::PrinMatrix() const
{
	for (std::vector<type> vector : matrix)
	{
		for (auto element : vector) {
			std::cout << " | " << element;
		}
		std::cout << " | " << std::endl;
	}
}

template<typename type, int m_size>
void Matrix<type,m_size>::Transposition()
{
}

//Sa dwie funkcje wyznacznika, jedna zmienia macierz (P) , a druga nie
//Determinant Liczy wyznacznik
template<typename type, int m_size>
type Matrix<type,m_size>::Determinant()
{
	auto matrix = this->matrix;
	const int unsigned ms = matrix.size();
	for (unsigned int i = 0; i < ms; i++) {
		// szuka maximum w kolumnie
		type maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for (unsigned int k = i + 1; k < ms; k++) {
			if (abs(matrix[k][i]) > maxEl) {
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}
		
		// zamienia maxymalny rzad z bierzacym
		for (unsigned int k = i; k < ms + 1; k++) {
			type temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (unsigned int k = i + 1; k < ms; k++) {
			type c = (matrix[k][i] / matrix[i][i]) * -1;
			for (unsigned int j = i; j < ms + 1; j++) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] += (c * matrix[i][j]);
				}
			}
		}
	}

	type det = 1;
	for (unsigned int i = 0; i < ms; ++i) {
		det *= matrix[i][i];
	}
	return det;
}

//DeterminantP liczy wyznacznik I zmienia tablice (P == pointer)
template<typename type, int m_size>
inline type Matrix<type,m_size>::DeterminantP()
{
	const int unsigned ms = this->matrix.size();
	for (unsigned int i = 0; i < ms; ++i) {
		// szuka maximum w kolumnie
		type maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for (unsigned int k = i + 1; k < ms; ++k) {
			if (abs(matrix[k][i]) > maxEl) {
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}

		// zamienia maxymalny rzad z bierzacym
		for (unsigned int k = i; k < ms + 1; ++k) {
			type temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (unsigned int k = i + 1; k < ms; ++k) {
			type c = (matrix[k][i] / matrix[i][i]) * -1;
			for (unsigned int j = i; j < ms + 1; ++j) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] += (c * matrix[i][j]);
				}
			}
		}
	}

	type det = 1;
	for (unsigned int i = 0; i < ms; ++i) {
		det *= matrix[i][i];
	}
	return det;
}

template<typename type, int m_size>
inline std::vector<type> Matrix<type,m_size>::Determinant(char a)
{
	auto matrix = this->matrix;
	const int unsigned ms = matrix.size();
	for (unsigned int i = 0; i < ms; i++) {
		// szuka maximum w kolumnie
		type maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for (unsigned int k = i + 1; k < ms; k++) {
			if (abs(matrix[k][i]) > maxEl) {
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}
		
		// zamienia maxymalny rzad z bierzacym
		for (unsigned int k = i; k < ms + 1; k++) {
			type temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (unsigned int k = i + 1; k < ms; k++) {
			type c = (matrix[k][i] / matrix[i][i]) * -1;
			for (unsigned int j = i; j < ms + 1; j++) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] += (c * matrix[i][j]);
				}
			}
		}
	}

	std::vector<type> det;
	for (unsigned int i = 0; i < ms; ++i) {
		det.push_back(matrix[i][i]);
	}
	return det;
}
template<typename type, int m_size>
std::vector<std::vector<type>>& Matrix<type,m_size>::GeMatrix()
{
	return this->matrix;
}

template<typename type, int m_size>
Matrix<type,m_size> Matrix<type,m_size>::operator*(const Matrix & other) const
{
	//Probowalem zrobic algorytm Strassena, ale mi nie wychodzilo
	//wiec postanowilem zrobic zwyklym sposobem
	const unsigned int msr1 = this->matrix.size();
	const unsigned int msc2 = other.matrix[0].size();
	const unsigned int msc1 = this->matrix[0].size();
	//Szczerze mowiac, lepiej sie czuje z std::vector niz zwyklymi 2D array
	std::vector<type> vec(0, msr1);
	std::vector < std::vector<type> > temp(msc2, vec);
	if (msr1 == msc2)
	{
		for (int i = 0; i < msr1; ++i)
		{
			for (int j = 0; j < msc2; ++j)
			{
				for (int k = 0; k < msc1; ++k)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
	}
	else std::cerr << "Wrong Matrix sizes" << std::endl;
	return Matrix(temp);
}

template<typename type, int m_size>
Matrix<type,m_size> Matrix<type,m_size>::operator*(const double other) const
{
	std::vector<type> vec;
	std::vector < std::vector<type> > temp;
	for (auto vec : this->matrix)
	{
		for (auto el : vec)
		{
			vec.emplace_back(el*other);
		}
		temp.emplace_back(vec);
		vec.clear();
	}
	return Matrix(temp);
}

template<typename type, int m_size>
std::vector<type> Matrix<type,m_size>::operator[](const unsigned int index) const
{
	try {
		return (this->matrix).at(index % this->matrix.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->matrix).at(0);
	}
}

template<typename type, int m_size>
std::vector<type>& Matrix<type,m_size>::operator[](const unsigned int index)
{
	try {
		return (this->matrix).at(index % this->matrix.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->matrix).at(0);
	}
}
#endif // !HH_Matrix