#ifndef H_CUBOID
#define H_CUBOID
#include "Vector3D.h"
#include <vector>
#include <string>
#include "G_Shape.h"


const std::string kModelCuboid("solid/model.dat");

class Cuboid: public G_Shape 
{
private:
	std::vector<Vector3D> points;
	Vector3D translation = {0,0,0};
	double angle = 0;
	double angleY = 0;
	std::string filename;
	mutable std::vector<Vector3D> PFR;
public:  
	Cuboid();
	Cuboid(std::string s_filename);
	inline std::string GetName() const override {return "Cuboid";};
	void Rotate(const double& other);
	void RotationY(const double& angleY);
	void draw() const;
	void translate(const Vector3D& change);
	void Rot(double s_angle);
	void Move(double s_distance,double s_angle);
	~Cuboid();
};

#endif