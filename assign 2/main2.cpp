//This program gets an array from a file and sorts the array using a seperate pointer.
//Then it prints out the sorted pointer as well as the original array

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <memory>
using namespace std;

const int MAX_ARRAY = 10;

bool readIntoDataArray(ifstream&, int [],unsigned int&, int* []);
void sort(int* [] , unsigned int);
void displayArray(int[], unsigned int);
void displayArray(int* [], unsigned int);
void swapIntPtr(int** , int**);   

int main()
{
    int dataArray[MAX_ARRAY];
    int *ptrArray[MAX_ARRAY];
    unsigned int count;
    string fileName = "arrayData.txt";
    ifstream inputFile;

    inputFile.open(fileName);

    if(inputFile)
    {
        do{
            if(readIntoDataArray(inputFile, dataArray, count, ptrArray))
                break;

            sort(ptrArray, count);
            displayArray(ptrArray, count);
            displayArray(dataArray, count);
 
            cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();

            for(int i = 0; i < count; i++)
            {
                delete ptrArray[i];
            }

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

//this function reads the file and stores the values in the array and creates the pointer 

bool readIntoDataArray(ifstream &inputFile, int donations[],unsigned int &count, int * ptrArray[])
{
    bool end = false;

    if(inputFile >> count)
    {
        for(int counter = 0; counter < count; counter++)
        {
            inputFile >> donations[counter];
            ptrArray[counter] = new int(donations[counter]);
        }

    }
    else 
    {
        end = true;
    }

    return end;
}

//this function sorts the pointer in to ascending order

void sort(int *pointerArray[MAX_ARRAY], unsigned int size)
{
    bool swap;

    do
    {
        swap = false;
       for(int counter = 0; counter < (size -1); counter++)
       {
            if(*(pointerArray[counter]) > *(pointerArray[counter + 1]))
            {
                swapIntPtr((pointerArray + counter), (pointerArray + counter + 1));
                swap = true;
            }
       }
    } while (swap);
    
}

//this function creates the swap if the numbers in the pointer need to be swapped 

void swapIntPtr(int ** greater, int ** less)
{
    int temp = **(greater);
    **greater = **less;
    **less = temp;
}

//this function displays the original array 

void displayArray(int dataArray[], unsigned int maxElements)
{
    cout << "Data Array elements are:" << endl;

    for(int counter = 0; counter < maxElements; counter++)
    {
        cout << setw(6) << dataArray[counter];
    }
    
    cout << endl;
}

//this function displays the pointer 

void displayArray(int* pointerArray[], unsigned int maxElements)
{
    cout << "The Pointer Array of sorted pointer elements:" << endl;

    for(int counter = 0; counter < maxElements; counter++)
    {
        cout << setw(6) << *(pointerArray[counter]);
    }

    cout << endl;
}

