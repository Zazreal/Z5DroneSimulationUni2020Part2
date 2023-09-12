#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#include "../inc/Obstacles.h"
#include "../inc/Scene.h"
#include "../inc/gnuplot_link.hh"
#include "../inc/Vector3D.h"
#include "../inc/Cuboid.h"
#include "../inc/Drone.h"

using namespace std;


const string kDroneFile("solid/drone.dat");
const string Sea_Floor_File("solid/floor.dat");
const string Water_Surface_File("solid/water.dat");
const string Prism_1("solid/prismX.dat");
const string Prism_2("solid/prismY.dat");
const string plate("solid/plate.dat");
const string rod("solid/Rod.dat");
const string Cube("solid/Cuboid.dat");

void ThreadFunction(const int& breaker,const Drone& drone);
int main()
{
	std::cout<<"Program Start" <<std::endl;
	double distance = 0, angle = 0;
	int menu = 0;
	//bool collision = false;
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	Drone Drone1(kDroneFile,Prism_1,Prism_2);        // To tylko przykladowe definicje zmiennej
	Drone1.draw();
	

	std::thread DrawThread(ThreadFunction, std::ref(menu),std::ref(Drone1));

	cout << "Press ENTER, to continue" << endl;
	cin.ignore(100000, '\n');
	while (menu != -1)
	{
		std::cout << 
		R"(Menu:
		Enter 1 to rotate the drone (Z axis)
		Enter 2 to move the drone
		Enter 3 to move the drone at an angle
		Enter 4 to rotate the drone (Y axis)
		Enter 5 to print obstacles 
		Enter -1 to end the program)" << std::endl;

		std::cout<<"Current Vector3D count: "<<Vector3D::return_current_count()<<std::endl;
		std::cout<<"Total Vector 3D count: "<<Vector3D::return_total_count()<<std::endl;

		std::cin >> menu;
		switch (menu)
		{
		case 1: std::cout << "Enter the angle: ";
			std::cin >> angle;
			for (int i = 0; i < 120; ++i)
			{
				Drone1.Rot(angle);
				//link.Draw();
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break;
		case 2: std::cout << "Enter the distance: ";
			std::cin >> distance;
			for (int i = 0; i < 120; ++i)
			{

				Drone1.Move(distance, 0);
				if(true == Drone1.checkCollisions())
				{
					i = 120;
				}
				Drone1.Move(-(distance/abs(distance)), 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break; 
		case 3:
			std::cout << "Enter the distance: ";
			std::cin >> distance;
			std::cout << "Enter the angle: ";
			std::cin >> angle;
			for (int i = 0; i < 120; ++i)
			{
				Drone1.Move(distance, angle);
				if(true == Drone1.checkCollisions())
				{
					i = 120;
				}
				Drone1.Move(-(distance/abs(distance)), 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break;
		case 4:
		std::cout << "Enter the angle: ";
			std::cin >> angle;
			for (int i = 0; i < 120; ++i)
			{
				Drone1.RotationY(angle);
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
		break;
		case 5:
			for(const auto& el: scene->obstacles)
			{
				std::cout<<"Obstacle: "<<el->GetName()<<std::endl;
			}
			break;
		case -1:
			menu = -1;
			break;

		}
	}
	if(DrawThread.joinable() == true)DrawThread.join();
	return EXIT_SUCCESS;
}

void ThreadFunction(const int& breaker,const Drone& drone)
{
	PzG::GnuplotLink link; // Ta zmienna jest potrzebna do wizualizacji
	link.Init();
	link.AddFilename(kDroneFile.c_str(), PzG::LS_CONTINUOUS, 1);
	//link.AddFilename(Water_Surface_File.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(Sea_Floor_File.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(Prism_1.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(Prism_2.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(plate.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(rod.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(Cube.c_str(),PzG::LS_CONTINUOUS,1);
	link.SetDrawingMode(PzG::DM_3D);
	link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
	//std::cout<<std::this_thread::get_id()<<std::endl;
	while(-1 != breaker)
	{
		drone.ConstAnimate();
		link.Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
		
	}
}