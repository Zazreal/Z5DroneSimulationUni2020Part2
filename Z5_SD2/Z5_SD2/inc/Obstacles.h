#ifndef H_OBSTACLES
#define H_OBSTACLES
#include "G_Shape.h"
#include "Cuboid.h"
#include "Prism.h"
#include <memory>
#include <vector>
#include <string>

namespace Obstacles
{

    class Plate: public G_Shape
    {
    public:
  
        virtual std::string GetName() const override {return "Plate";}

        Plate(std::string filename) 
        {
            Cuboid *shape = new Cuboid(filename);
            points = shape->Getpoints();
            delete shape;
        }
    };

    class Rod: public G_Shape
    {
    public:

        virtual std::string GetName() const override {return "Rod";}

        Rod(std::string filename) 
        {
            Cuboid *shape = new Cuboid(filename);
            points = shape->Getpoints();
            delete shape;
        }
    };


    class Surface: public G_Shape
    {
    public:
        virtual std::string GetName() const override {return "Surface";}
        Surface(std::string filename) 
        {
            Cuboid *shape = new Cuboid(filename);
            points = shape->Getpoints();
            delete shape;
        }
    };
    class Floor: public G_Shape
    {
    public:
        virtual std::string GetName() const override {return "Floor";}
        Floor(std::string filename) 
        {
            Cuboid *shape = new Cuboid(filename);
            points = shape->Getpoints();
            delete shape;
        }
    };

};

#endif