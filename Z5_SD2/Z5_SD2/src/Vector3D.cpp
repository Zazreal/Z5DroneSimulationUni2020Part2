

#include "../inc/Vector3D.h"
#include <fstream>
unsigned int Vector3D::Vector3D_current_count = 0;
unsigned int Vector3D::Vector3D_total_count = 0;
int Vector3D::return_current_count()
{
	return Vector3D_current_count;
}
int Vector3D::return_total_count()
{
	return Vector3D_total_count;
}

Vector3D::Vector3D()
{
	++Vector3D_current_count;
	++Vector3D_total_count;
}
Vector3D::Vector3D(const Vector3D& other)
{
	++Vector3D_current_count;
	++Vector3D_total_count;
	this->vector = other.vector;	
}

Vector3D::Vector3D(double x, double y, double z)
{
	++Vector3D_current_count;
	++Vector3D_total_count;
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
}


Vector3D::Vector3D(const Vector<double,3>& other)
{
	++Vector3D_current_count;
	++Vector3D_total_count;
	this->vector = other.GetVector();
}

Vector3D::~Vector3D()
{
	--Vector3D_current_count;
}


std::istream & operator>>(std::istream & stream, Vector3D & vec)
{
	stream >> vec[0] >> vec[1] >> vec[2];
	return stream;
}
/*
std::ostream &operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream << vec[0] << vec[1] << vec[2] << std::endl;
	return stream;
}
*/