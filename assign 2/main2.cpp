//prologue

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ARRAY = 10;

bool readIntoDataArray(ifstream&, int [], int&);
void displayArray(int[], unsigned int);
void displayArray(int* [], unsigned int);

int main()
{
    int dataArray[MAX_ARRAY];
    int *ptrArray = nullptr;
    int count;
    string fileName = "arrayData.txt";
    ifstream inputFile;

    inputFile.open(fileName);

    if(inputFile)
    {
        do{
            if(readIntoDataArray(inputFile, dataArray, count))
                break;

            displayArray(dataArray, count);
            ptrArray = dataArray;
            displayArray(ptrArray, count);

            cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();

        }while(true);

    }
    else 
    {
        cout << "File " << fileName << " could not be opened!" << endl;
        cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
        exit(EXIT_FAILURE);
    }

    cout << "Program Done." << endl;
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

void displayArray(int dataArray[], unsigned int maxElements)
{
    cout << "Data Array elements are:" << endl;

    for(int counter = 0; counter < maxElements; counter++)
    {
        cout << setw(6) << dataArray[counter];
    }
    
    cout << endl;
}

void displayArray(int* pointerArray[], unsigned int maxElements)
{
    cout << "The Pointer Array of sorted pointer elements:" << endl;

    for(int counter = 0; counter < maxElements; counter++)
    {
        cout << setw(6) << pointerArray[counter];
    }

    cout << endl;
}
