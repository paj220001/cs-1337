//prologue

#include <iostream>
#include <fstream>
#include <memory> 
#include <string>
#include <stdio.h>
using namespace std;

const int MAX_ARRAY = 10;

bool readIntoDataArray(ifstream&, int [], int&);

int main()
{
    int donationsArray[MAX_ARRAY];
    int *ptrArray = nullptr;
    int count;
    string fileName = "arrayData.txt";
    ifstream inputFile;

    inputFile.open(fileName);

    if(inputFile)
    {
        do{
            if(readIntoDataArray(inputFile, donationsArray, count))
                break;

        }while(true);
    }
    else 
    {
        cout << "File " << fileName << " could not be opened!" << endl;
        cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
      exit(EXIT_FAILURE);
    }
}


bool readIntoDataArray(ifstream &inputFile, int donations[], int &count)
{
    bool end = false;

    if(inputFile >> count)
    {
        for(int counter = 0; counter < count; counter++)
        {
            inputFile >> donations[counter];
        }
    }
    else 
    {
        end = true;
    }

    return end;
}
