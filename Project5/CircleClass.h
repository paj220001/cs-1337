//Pranav Joseph paj220001
#ifndef CIRCLE_CLASS
#define CIRCLE_CLASS
#include "BasicShapeClass.h"
#include "LineInfo.h"
#include <iostream>
#include <string>
using namespace std;

class CircleClass : public BasicShapeClass
{
private:
   const double PI = 3.14159;
   double centerX;
   double centerY;
   double radius;
public:
   CircleClass(double x, double y, double radi)
   {
      if (x < 0 || y < 0 || radi < 0)
      {
         string errorString = "";
         if (x < 0)
            errorString += "centerX is negative\n";
         if(y < 0)
            errorString += "centerY is negative\n";
         if(radi < 0)
            errorString += "radius is negative\n";

         throw domain_error(LineInfo(errorString, __FILE__, __LINE__));

      }
      else
      {
         centerX = x;
         centerY = y;
         radius = radi;
         double area = calculateArea();
         setArea(area);
      }
   }


   virtual double calculateArea() override 
   {
      double temp_area;
      temp_area = PI * radius * radius;
      return temp_area;
   }


   virtual void display() const override
   {
      cout << "Shape is a Circle :"
           << "Center X : " << centerX << endl
           << "Center Y : " << centerY << endl
           << "Radius   : " << radius << endl
           << "Area     : " << getArea() << endl << endl;
   }


};

#endif 

