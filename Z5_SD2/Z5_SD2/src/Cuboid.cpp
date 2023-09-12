#include "../inc/Cuboid.h"
#include "../inc/Matrix.hh"
#include "../inc/SystemOfLinearEquations.hh"
#include <fstream>
#include <iostream>
#include <cmath>
Cuboid::Cuboid()
{
	//std::cout<<"Default Constructor" <<std::endl;
	std::ifstream inputFile;
	//std::cout<<kModelCuboid<<std::endl;
	inputFile.open(kModelCuboid);
	//std::cout<<"File opened" << kModelCuboid<<std::endl;
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Cuboid file!"
			<< std::endl;
		return;
	}
	Vector3D point;
	while (inputFile >> point)
	{
		//std::cout<<"Point: "<<point<<std::endl;
		points.emplace_back(point);
	}
	inputFile.close();
//	std::cout<<"endl Constructor: Default\n";
}

Cuboid::Cuboid(std::string s_filename): filename{s_filename}// , angle {0},translation{0,0,0}
{
	//std::cout<<"string Constructor" <<std::endl;
	std::ifstream inputFile;
	//std::cout<<kModelCuboid<<std::endl;
	inputFile.open(kModelCuboid);
	//std::cout<<"File opened " << kModelCuboid<<std::endl;
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Cuboid file!"
			<< std::endl;
		return;
	} 
	//std::cout<<"Init vec temp"<<std::endl;
	Vector3D point; 
	//std::cout<<"starting reading\n";
	while (inputFile >> point)
	{
		points.emplace_back(point);
	}
	inputFile.close();
	//std::cout<<"endl Constructor: string\n";
}

void Cuboid::draw() const
{
	//std::cout<<"start drawing\n";
	std::ofstream outputFile;
	outputFile.open(filename);
	if (!outputFile.is_open())
	{
		std::cerr << "Unable to open drone file!" << std::endl;
		return;
	}
	//std::cout<<"Angle"<<this->angle << std::endl;

	std::vector<std::vector<double>> Rot_By_Z = 
	{
		{std::cos(angle),-std::sin(angle),0},
		{std::sin(angle),std::cos(angle),0},
		{0,0,1}
	};
	std::vector<std::vector<double>> Rot_By_Y = 
	{
		{std::cos(angleY),-0,std::sin(angleY)},
		{0,1,0},
		{-std::sin(angleY),0,std::cos(angleY)}
	};
	Vector3D RotV;
	std::vector<Vector3D> RotationYvector;
	Matrix<double,3> Rotation_MatrixZ;
	Matrix<double,3> Rotation_MatrixY;
	//std::cout<<"Angle: " << this->angle << std::endl;
	if(angleY != 0){
	for (unsigned i = 0; i < points.size(); ++i)
	{
		Rotation_MatrixZ = Rot_By_Z;
		Rotation_MatrixZ.AddEl(points[i].GetVector());
		SystemOfLinearEquations<double> SoLE(Rotation_MatrixZ);
		SoLE.Gauss();
		RotV = SoLE.Result();
		RotationYvector.emplace_back(RotV);
	}
	for (unsigned i = 0; i < points.size(); ++i)
	{
		Rotation_MatrixY = Rot_By_Y;
		Rotation_MatrixY.AddEl(RotationYvector[i].GetVector());
		SystemOfLinearEquations<double> SoLE(Rotation_MatrixY);
		SoLE.Gauss();
		RotV = SoLE.Result();
		outputFile << RotV + translation << std::endl;
		if (i % 4 == 3) // triggers after every 4 points
		{
			outputFile << "#\n\n";
		}
	}
	}else
	{
		for (unsigned i = 0; i < points.size(); ++i)
	{
		Rotation_MatrixZ = Rot_By_Z;
		Rotation_MatrixZ.AddEl(points[i].GetVector());
		SystemOfLinearEquations<double> SoLE(Rotation_MatrixZ);
		SoLE.Gauss();
		RotV = SoLE.Result();
		outputFile << RotV + translation << std::endl;
		if (i % 4 == 3) // triggers after every 4 points
		{
			outputFile << "#\n\n";
		}
	}
	}
	
	outputFile.close();
	//std::cout<<"End drawing"<<std::endl;
}

void Cuboid::Rotate(const double & other)
{
	this->angle = this->angle + other;
	if(angle>6.28318) angle-=6.28318;
}

void Cuboid::translate(const Vector3D& change)
{
	translation = translation + change;
}

void Cuboid::Rot(double s_angle)
{
	double ua = s_angle / 120;
	Rotate(ua);
	this->draw();

}

void Cuboid::Move(double s_distance,double s_angle)
{
	double ud = s_distance/120;
	Vector3D movement(cos(s_angle)*ud,0,sin(s_angle)*ud);
	translate(movement);
	this->draw();

}

void Cuboid::RotationY(const double& angY)
{
	double ua = angY / 120;
	this->angleY = this->angleY + ua;
	if(angleY>6.28318) angleY-=6.28318;
	this->draw();
}

Cuboid::~Cuboid()
{
}
