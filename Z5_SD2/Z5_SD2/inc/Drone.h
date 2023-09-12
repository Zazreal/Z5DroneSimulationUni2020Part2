#ifndef H_Drone
#define H_Drone
#include "Cuboid.h"
#include "Prism.h"
#include "Scene.h"

class Drone
{
private:
double angle;
Vector3D outline = {60,60,60};
Vector3D translation = {0,0,0};
Cuboid Hull;
Prism Rotor1;
Prism Rotor2;
Scene scene;
public:
    Drone();
    Drone(std::string Hull_Fname,std::string Rotor1_Fname, std::string Rotor2_Fname);
    void ConstAnimate() const;
    void Rotate(const double& other);
    void RotationY(const double& angY);
	void draw() const;
	void translate(const Vector3D& change);
	void Move(double s_distance, double s_angle);
    void Rot(const double& s_angle);
    bool checkCollisions() const;
    ~Drone();
};

#endif