//Pranav Joseph paj220001

#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS
#include "BasicShapeClass.h"
#include "LineInfo.h"
#include <iostream>
#include <string>
using namespace std;

class RectangleClass : public BasicShapeClass
{
private:
   double width, length;

public:
   RectangleClass(double w, double l)
   {
      if (w >= 0 && l >= 0)
      {
         width = w;
         length = l;
         double area = calculateArea();
         setArea(area);
      }
      else
      {
         string errorString = "";
         if (width < 0)
            errorString += "width is negative\n";
         if (length < 0)
            errorString += "length is negative\n";
         throw domain_error(LineInfo(errorString, __FILE__, __LINE__));
      }
   }

   virtual double calculateArea() override
   {
      double temp_area;
      temp_area = width * length;
      return temp_area;
   }


   virtual void display() const override
   {
      cout << "Shape is a Rectangle :" << endl
         << "Width  : " << width << endl
         << "Length : " << length << endl
         << "Area   : " << getArea() << endl << endl;
   }
};



#endif // !RECTANGLE_CLASS
