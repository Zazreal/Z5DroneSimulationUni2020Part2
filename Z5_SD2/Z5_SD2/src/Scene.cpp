#include "../inc/Scene.h"
#include <memory>

const std::string Sea_Floor_File("solid/floor.dat");
const std::string Water_Surface_File("solid/water.dat");
const std::string plate("solid/plate.dat");
const std::string rod("solid/Rod.dat");
const std::string Cube("solid/Cuboid.dat");

Scene::Scene()
{
    this->obstacles.emplace_back(std::make_shared<Cuboid>(Cube));
    this->obstacles.emplace_back(std::make_shared<Obstacles::Plate>(plate));
    this->obstacles.emplace_back(std::make_shared<Obstacles::Rod>(rod));
    this->obstacles.emplace_back(std::make_shared<Obstacles::Floor>(Sea_Floor_File));
    this->obstacles.emplace_back(std::make_shared<Obstacles::Surface>(Water_Surface_File));
}