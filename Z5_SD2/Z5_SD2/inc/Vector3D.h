#ifndef HH_VECTOR3D
#define HH_VECTOR3D

#include "Vector.hh"



class Vector3D :public Vector<double,3>
{
private:
	static unsigned int Vector3D_current_count;
	static unsigned int Vector3D_total_count;
public:
	static int return_current_count();
	static int return_total_count();
	Vector3D();
	Vector3D(const Vector3D& other);
	Vector3D(double x, double y, double z);
	Vector3D(const Vector<double, 3>& other);
	~Vector3D();
	friend std::istream & operator>>(std::istream& stream, Vector3D& vec);
	//friend std::ostream &operator<<(std::ostream& stream, Vector3D& vec);
};

std::istream & operator>>(std::istream& stream, Vector3D& vec);
//std::ostream &operator<<(std::ostream& stream, Vector3D& vec);

#endif