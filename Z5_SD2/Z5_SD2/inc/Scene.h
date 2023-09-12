#ifndef H_SCENE
#define H_SCENE
#include "G_Shape.h"
#include "Obstacles.h"
#include <memory>
#include <vector>


class Scene
{
private:
public:
Scene();
std::vector<std::shared_ptr<G_Shape>> obstacles;
};


#endif