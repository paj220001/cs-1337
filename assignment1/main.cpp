 // this program gets matrixes from a text file and looks to see if those matrixes have vertical symetry. If they do it will print yes 
// if not it it will print out no. Then it will sort the a row in the matrix from smallest to largest and print out the matrix again

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const unsigned MAX_MATRIX_SIZE = 20;
const unsigned WIDTH_DISPLAY = 12;

bool readMatrixFromFile(int[][MAX_MATRIX_SIZE], unsigned&, unsigned&, ifstream&);
void displayMatrix(int[][MAX_MATRIX_SIZE], unsigned, unsigned);
void displayCalcMatrixSums(int[][MAX_MATRIX_SIZE], unsigned, unsigned, int[MAX_MATRIX_SIZE]);
void symmetryCheckMatrix(int[], unsigned, unsigned);
void sortMatrixRows (int [][MAX_MATRIX_SIZE], unsigned,  unsigned);


int main() {
   unsigned height, width;
   int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], colSums[MAX_MATRIX_SIZE];
   string   INPUT_FILE_NAME = "matrixes.txt";
   ifstream inputFileStreamObj(INPUT_FILE_NAME);

   if (inputFileStreamObj.fail())
   {
      cout << "File " << INPUT_FILE_NAME << " could not be opened !" << endl;
      cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
      exit(EXIT_FAILURE);
   }

   do {

      if (readMatrixFromFile(matrix, height, width, inputFileStreamObj))
         break;

      cout << "Input:" << endl;
      displayMatrix(matrix, height, width);
      displayCalcMatrixSums(matrix, height, width, colSums);
      symmetryCheckMatrix(colSums, width, height);
      sortMatrixRows       (matrix,  width, height);
      cout << "Sorted:" << endl;
      displayMatrix        (matrix, height, width);

      cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();

   } while (true);

   cout << "Program Done" << endl;

   exit(EXIT_SUCCESS);
}

bool readMatrixFromFile(int matrix[][MAX_MATRIX_SIZE], unsigned& height, unsigned& width, ifstream& inputFileStreamObj)
{
   bool end = false;

   if (inputFileStreamObj >> height >> width)
   {

      for (unsigned int heightCounter = 0; heightCounter < height; heightCounter++)
      {
         for (unsigned int widthCounter = 0; widthCounter < width; widthCounter++)
         {
            inputFileStreamObj >> matrix[heightCounter][widthCounter];
         }
      }
   }
   else
   {
      end = true;
   }

   return(end);
}


void displayMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width)
{
   for (unsigned int heightCounter = 0; heightCounter < height; heightCounter++)
   {
      for (unsigned int widthCounter = 0; widthCounter < width; widthCounter++)
      {
         cout << "\t" << setw(4) << matrix[heightCounter][widthCounter];
      }

      cout << endl;
   }
}


void displayCalcMatrixSums(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width, int colSums[MAX_MATRIX_SIZE])
{
   int total;

   cout << "Sum: " << endl;

   for (unsigned int widthCounter = 0; widthCounter < width; widthCounter++)
   {
      total = 0;
      colSums[widthCounter] = 0;

      for (unsigned int heightCounter = 0; heightCounter < height; heightCounter++)
      {
         colSums[widthCounter] += matrix[heightCounter][widthCounter];
         total = colSums[widthCounter];

      }

      cout << "\t" << setw(4) << total;
   }
}


void symmetryCheckMatrix(int colSums[], unsigned width, unsigned height)
{
   cout << endl << endl << "Vertical Symetry: ";

   int sumLeftColumn, sumRightColumn;
   for (unsigned int widthCounter = 0; widthCounter < width / 2; widthCounter++)
   {
      sumLeftColumn = 0; sumRightColumn = 0;
      sumLeftColumn += colSums[widthCounter];
      sumRightColumn += colSums[width - widthCounter - 1];

      if (sumLeftColumn != sumRightColumn)
      {
         cout << "No" << endl << endl;
         return;
      }
   }

   cout << "Yes" << endl << endl;
}

void sortMatrixRows(int matrix[][MAX_MATRIX_SIZE], unsigned width, unsigned height)
{
  bool swap;
  int temp;

  do 
  {
    swap = false;
    for (unsigned int heightCounter = 0; heightCounter < height; heightCounter++)
    {
      for (unsigned int widthCounter = 0; widthCounter < (width - 1); widthCounter++)
      {
         if(matrix[heightCounter][widthCounter] > matrix[heightCounter][widthCounter + 1])
         {
            temp = matrix[heightCounter][widthCounter];
            matrix[heightCounter][widthCounter] = matrix[heightCounter][widthCounter + 1];
            matrix[heightCounter][widthCounter + 1] = temp;
            swap = true;
         }
      }
    }
  }while(swap);

}
