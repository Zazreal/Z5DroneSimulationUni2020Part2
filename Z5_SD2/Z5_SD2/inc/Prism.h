#ifndef H_Prism
#define H_Prism
#include "Vector3D.h"
#include <vector>
#include <string>
#include "G_Shape.h"

const std::string PrismModel("solid/prismX_model.dat");

class Prism: public G_Shape 
{
private:
	std::vector<Vector3D> points;
	mutable std::vector<Vector3D> PFR;
	Vector3D translation = {0,0,0};
	double angle = 0;
	double angleY = 0;
	std::string filename;
	Vector3D mountpoint= {0,0,0};
	mutable Vector3D current_mountpoint = {0,0,0};
	void WriteToFile(std::vector<Vector3D> vec) const;
public:  
	Prism();
	Prism(std::string s_filename);
	inline std::string GetName() const override {return "Prism";};
	void RotateY() const;
	void Rotate(const double& other);
	void RotationY(const double& angY);
	void draw() const;
	void translate(const Vector3D& change);
	void Rot_Move(double s_angle);
	void MountPoint(Vector3D& mountpoint);
	void Move(double s_distance, double s_angle);
	~Prism();

};

#endif