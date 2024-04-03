#ifndef BASIC_SHAPE_CLASS_H
#define BASIC_SHAPE_CLASS_H

class BasicShapeClass
{
   private:
      double area;
   public:
      double getArea() const
      { 
         return area; 
      }

      void setArea(double c)
      {
         area = c;
      }

      virtual double calculateArea() = 0;

      virtual void display() const = 0;
};


#endif 
