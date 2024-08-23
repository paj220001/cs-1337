#include <iostream>
#include "CircleClass.h"
#include "RectangleClass.h"
using namespace std;

const int MAX_SHAPES = 3;

int main()
{
   BasicShapeClass* shapeArray[MAX_SHAPES];
   double x, y, radius, length, width;
   unsigned shape_choice;
   cout << "Choose 3 Shapes and enter attributes,\n"
      << "when all 3 shapes are entered the calculated results for all 3 shapes will\n display\n\n";


   for (int count = 0; count < MAX_SHAPES;)
   {
      cout << "Choose your shape :\n\n"
         << "1. Circle\n"
         << "2. Rectangle\n\n"
         << "Enter your choice : ";
      cin >> shape_choice;

      if (shape_choice == 1 || shape_choice == 2)
      {
         try
         {
            if (shape_choice == 1)
            {
               cout << "\n\n"
                  << "Enter the circles x, y, and radius : ";
               cin >> x >> y >> radius;
               shapeArray[count] = new CircleClass(x, y, radius);
            }
            else
            {
               cout << "\n\n"
                  << "Enter the circles width, length : ";
               cin >> width >> length;
               shapeArray[count] = new RectangleClass(width, length);
            }
            count++;

            cout << endl;
         }
         catch (exception& e)
         {
            cout << e.what() << endl;
            cout << endl << "Press the enter key once or twice to leave..." << endl;
            cin.ignore(); cin.get();
            exit(EXIT_FAILURE);
         }
      }
      else
      {
         cout << "\n\n"
            << "Wrong menu value : " << shape_choice << endl
            << "Please try again...." << endl << endl;
      }
   }

   for (int count = 0; count < MAX_SHAPES; count++)
   {
      shapeArray[count]->display();
      delete shapeArray[count];
   }

   return 0;

}