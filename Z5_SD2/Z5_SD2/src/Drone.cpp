#include "..//inc/Drone.h"
#include "../inc/Matrix.hh"
#include "../inc/SystemOfLinearEquations.hh"
#include <fstream>
#include <iostream>
#include <cmath>
#include <memory>
static Vector3D RotVec1(-20,-45,0);
static Vector3D RotVec2(20,-45,0);
Drone::Drone()
{
}

Drone::Drone(std::string Hull_Fname,std::string Rotor1_Fname, std::string Rotor2_Fname): 
Hull(Hull_Fname), Rotor1(Rotor1_Fname), Rotor2(Rotor2_Fname)// , angle {0},translation{0,0,0}
{
    Rotor1.translate({0,-0,40});
    Rotor2.translate({0,-0,40});
    Rot(0);
    RotationY(0);
}

void Drone::draw() const
{
    Hull.draw();
    Rotor1.draw();
    Rotor2.draw();
}

void Drone::Rotate(const double & s_angle)
{
    Hull.Rot(s_angle);
    Rotor1.Rot_Move(s_angle);
    Rotor2.Rot_Move(s_angle);
}
void Drone::RotationY(const double & angY)
{   
    Rotor1.MountPoint(RotVec1);
    Rotor2.MountPoint(RotVec2);
    Hull.RotationY(angY);
    Rotor1.RotationY(angY);
    Rotor2.RotationY(angY);
}
void Drone::translate(const Vector3D& change)
{
    translation = translation + change;
	Hull.translate(change);
    Rotor1.translate(change);
    Rotor2.translate(change);
    
}

void Drone::Move(double s_distance, double s_angle)
{
    double ud = s_distance/120;
	Vector3D movement(cos(s_angle)*ud,0,sin(s_angle)*ud);
	translation = translation + movement;

    Rotor1.Move(s_distance,s_angle);
    Rotor2.Move(s_distance,s_angle);
    Hull.Move(s_distance,s_angle);
}
void Drone::Rot(const double& s_angle)
{
    //double mult = std::sqrt(2424);
    //double cangle = s_angle/120;
    //double div = 4/std::sqrt(97);
    //Vector3D RotVec1(mult*sin(cangle+4/std::sqrt(97)),-mult*cos(cangle+11/std::sqrt(97)),0);
    //Vector3D RotVec2(mult*sin(cangle-4/std::sqrt(97)),-mult*cos(cangle+11/std::sqrt(97)),0);
    Rotor1.MountPoint(RotVec1);
    Rotor2.MountPoint(RotVec2);
    Rotor1.Rot_Move(s_angle);
    Rotor2.Rot_Move(s_angle);
	Hull.Rot(s_angle);
}

void Drone::ConstAnimate() const
{
    Rotor1.RotateY();
    Rotor2.RotateY();
}

bool Drone::checkCollisions() const
{
    Vector3D centerOutline(outline/2);
    centerOutline[2] -= 20; //Dron na poczatku jest o 20 wyzej od srodka ukladu
    Vector3D minValues = translation - centerOutline;
    Vector3D maxValues = translation + outline - centerOutline;
    Vector3D point;
    //std::cout<<translation<<std::endl<<minValues<<std::endl<<maxValues<<std::endl;
    int overlap;
    for(unsigned i = 0; i < scene.obstacles.size(); ++i)
        for(unsigned j = 0; j < scene.obstacles[i]->Getpoints().size(); ++j)
        {
            point = scene.obstacles[i]->Getpoints()[j];
            for(unsigned k = 0; k < 3; ++k)
                if((point[k] < maxValues[k]) && (point[k] > minValues[k]))
                    overlap += 1;
            if(overlap == 3)
            {
                std::cerr << "Wykryto kolizje z: " << scene.obstacles[i]->GetName() 
                        << std::endl;
                return true;
            }
            overlap = 0;
        }

    return false;
}
Drone::~Drone()
{
}

