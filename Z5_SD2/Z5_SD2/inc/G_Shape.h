#ifndef H_G_SHAPE
#define H_G_SHAPE
#include <string>
#include "Vector3D.h"

class G_Shape
{
protected:
std::vector<Vector3D> points;
std::string filename;
Vector3D translation;
public:
G_Shape(){};
void draw() const;
virtual std::string GetName() const = 0;
std::vector<Vector3D> Getpoints() const {return points;}
//virtual void CheckColiision(G_Shape& obstacle);
virtual ~G_Shape(){};

};

#endif