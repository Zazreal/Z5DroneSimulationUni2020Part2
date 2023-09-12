#include "../inc/Prism.h"
#include "../inc/Matrix.hh"
#include "../inc/SystemOfLinearEquations.hh"
#include <fstream>
#include <iostream>
#include <cmath>
#include <mutex>
#include <thread>
#include <chrono>

static std::mutex mu;
static double ARY = 0;
Prism::Prism()
{
	//std::cout<<"Default Constructor" <<std::endl;
	std::ifstream inputFile;
	//std::cout<<PrismModel<<std::endl;
	inputFile.open(PrismModel);
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Prism file!"
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

Prism::Prism(std::string s_filename): filename{s_filename}// , angle {0},translation{0,0,0}
{
	//std::cout<<"string Constructor" <<std::endl;
	std::ifstream inputFile;
	//std::cout<<PrismModel<<std::endl;
	inputFile.open(PrismModel);
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Prism file!"
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

void Prism::draw() const
{
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
	Vector3D RotV,mountp;
	std::vector<Vector3D> ToFileVector;
	Matrix<double,3> Rotation_Matrix,Rotation_Matrix_mp(Rot_By_Z);
	Matrix<double,3> Rotation_MatrixY(Rot_By_Y);
	
	std::vector<double> mp = {mountpoint[0],mountpoint[1],mountpoint[2]};
	Rotation_Matrix_mp.AddEl(mp);
	SystemOfLinearEquations<double> SoLE_mp(Rotation_Matrix_mp);
	SoLE_mp.Gauss();
	mountp = SoLE_mp.Result();

	std::vector<double> mp2 = {mountp[0],mountp[1],mountp[2]};
	Rotation_MatrixY.AddEl(mp2);
	SystemOfLinearEquations<double> SoLE_mp2(Rotation_MatrixY);
	SoLE_mp2.Gauss();
	mountp = SoLE_mp2.Result();



	for (unsigned i = 0; i < points.size(); ++i)
	{ 
		Rotation_Matrix = Rot_By_Z;
		Rotation_Matrix.AddEl(points[i].GetVector());
		SystemOfLinearEquations<double> SoLE(Rotation_Matrix);
		SoLE.Gauss();
		RotV = SoLE.Result();
		PFR.emplace_back(RotV*18);
		ToFileVector.emplace_back(RotV*18 + mountp + translation);
	}
	WriteToFile(ToFileVector);
	current_mountpoint = mountp;
}

void Prism::Rotate(const double & other)
{
	this->angle = this->angle + other;
	if(angle>6.28318) angle-=6.28318;
}

void Prism::translate(const Vector3D& change)
{
	translation = translation + change;
}

void Prism::Move(double s_distance, double s_angle)
{
	double ud = s_distance/120;

	Vector3D movement(cos(s_angle)*ud,0,sin(s_angle)*ud);

	translate(movement);
	this->draw();

}

void Prism::Rot_Move(double s_angle)
{
	double ua = s_angle / 120;
	Rotate(ua);
	this->draw();

}
void Prism::RotationY(const double & angY)
{
	double ua = angY / 120;
	this->angle = this->angle + ua;
	if(angle>6.28318) angle-=6.28318;
	this->draw();
}


void Prism::RotateY() const
{
	ARY += 0.1;
	if(ARY>6.2831) ARY -= 6.2831;
	std::vector<std::vector<double>> Rot_By_Y = 
	{
		{std::cos(ARY),-0,std::sin(ARY)},
		{0,1,0},
		{-std::sin(ARY),0,std::cos(ARY)}
	};
	Vector3D RotV;
	std::vector<Vector3D> ToFileVector;
	Matrix<double,3> Rotation_Matrix;
	for (unsigned i = 0; i < PFR.size(); ++i)
	{ 
		Rotation_Matrix = Rot_By_Y;
		Rotation_Matrix.AddEl(PFR[i].GetVector());
		SystemOfLinearEquations<double> SoLE(Rotation_Matrix);
		SoLE.Gauss();
		RotV = SoLE.Result();
		ToFileVector.emplace_back(RotV + current_mountpoint + translation);
	}
	WriteToFile(ToFileVector);

}

void Prism::WriteToFile(std::vector<Vector3D> vec) const
{
	std::lock_guard<std::mutex> lock(mu);
	std::ofstream outputFile;
	outputFile.open(filename);
	if (!outputFile.is_open())
	{
		std::cerr << "Unable to open drone file!" << std::endl;
		return;
	}
	for (unsigned i = 0; i < vec.size(); ++i)
	{
		outputFile << vec[i] << std::endl;
		if (i % 4 == 3) // triggers after every 4 points
		{
			outputFile << "#\n\n";
		}
	}
	outputFile.close();
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

Prism::~Prism()
{
}

void Prism::MountPoint(Vector3D& mountpoint)
{
	this->mountpoint = mountpoint;
}