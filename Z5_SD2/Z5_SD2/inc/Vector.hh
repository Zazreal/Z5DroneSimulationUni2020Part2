#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#ifndef HH_VECTOR
#define HH_VECTOR

/*
	Klasa Vector zawiera std::vector
	dzieki czemu nie potrzebny jest znany rozmiar.
	Wszystkie metody klasy sluza do jego obslugi.
 */
template<typename T>
T string_to_template(std::string str);

template<typename type, int size>
class Vector
{
protected:
	std::vector<type> vector;
public:
	Vector();
	Vector(std::vector<type>& vec);
	~Vector();
	void SeVector(std::vector<type>& other);
	std::vector<type> GetVector() const;
	Vector operator=(const std::vector<type>& other);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator-();
	Vector operator*(const Vector& other) const;
	Vector operator*(const double multiplier) const;
	Vector operator/(const double divider) const;
	double operator[](const int index) const;
	double& operator[](const int index);
	friend std::istream & operator>>(std::istream& stream, Vector& vec)
	{
		std::string temp;
		type temp2;
		std::cout << "Inputing Vector, write \"stop\" to end input. " << std::endl;
		while (true)
		{
			getline(stream, temp);
			if ("stop" == temp) break;
			temp2 = string_to_template<type,size>(temp);
			vec.vector.emplace_back(temp2);
		}
		std::cout << "Vector input ended" << std::endl;
		return stream;
	}

	friend std::ostream &operator<<(std::ostream& stream, const Vector& vec)
	{
		for (unsigned int i = 0; i < vec.vector.size(); i++) {
			stream << "| x" << i + 1 << " | " << vec.vector[i] << " |" << std::endl;
		}
		return stream;
	}
	friend std::ofstream &operator<<(std::ofstream& stream, const Vector& vec)
	{
		for(auto el: vec.GetVector())
		{
			stream<<el<<" ";
		}
		return stream;
	}
};

template<typename type, int size>
Vector<type,size>::Vector()
{
	std::vector<type> temp(size);
	this->vector = temp;

}
template<typename type, int size>
Vector<type,size>::Vector(std::vector<type>& vec) : vector{ vec }
{
}

template<typename type, int size>
Vector<type,size>::~Vector<type,size>()
{
}

template<typename type, int size>
void Vector<type,size>::SeVector(std::vector<type>& other)
{
	this->vector = other;
}

template<typename type, int size>
inline std::vector<type> Vector<type,size>::GetVector() const
{
	return this->vector;
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator=(const std::vector<type>& other)
{
	this->vector = other;
	return *this;
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator+(const Vector& other) const
{
	//std::transform(this->vector.begin(), this->vector.end(), other.vector.begin(), this->vector.begin(), std::plus<int>());
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] + other.vector[i]);
		}
	}
	else std::cerr << "You Cant add vectors of diffrent sizes" << std::endl;
	return Vector(vec);
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator-(const Vector& other) const
{
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] - other.vector[i]);
		}
	}
	else std::cerr << "You Cant subtract vectors of diffrent sizes" << std::endl;
	return Vector(vec);
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator-()
{
	for (type element : this->vector)
		element *= (-1);
	return Vector(this->vector);
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator*(const Vector& other) const
{
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (unsigned int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] * other.vector[i]);
		}
	}
	return Vector(vec);
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator*(const double multiplier) const
{
	std::vector<type> vec;
	for (auto element : this->vector)
		vec.emplace_back(element * multiplier);
	return Vector(vec);
}

template<typename type, int size>
Vector<type,size> Vector<type,size>::operator/(const double divider) const
{
	std::vector<type> vec;
	for (auto element : this->vector)
		vec.emplace_back(element / divider);
	return Vector<type,size>(vec);
}

template<typename type, int size>
double Vector<type,size>::operator[](const int index) const
{
	try {
		return (this->vector).at(index % this->vector.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->vector).at(0);
	}
}

template<typename type, int size>
double& Vector<type,size>::operator[](const int index)
{
	try {
		return (this->vector).at(index % this->vector.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->vector).at(0);
	}
}


template<typename T>
T string_to_template(std::string str)
{
	T TC;
	std::stringstream convert(str);
	convert >> TC;
	return TC;
}

#endif