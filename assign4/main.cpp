//this program collects all the transactions for a hotdog stand. First it reads a file for the info about these hot dog stands 
//then stores this info into a array of a class which stores all the info for the hot dog stand. Then the program reads another file
// which has all the transactions a hot dog stands has. The program stores these transactions into an array of the transactions class 
//the program then updates each hot dog stand after the transaction and updates the info file with the most up to date information

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "HotDogStandsClass.h"
#include "TransactionClass.h"
using namespace std;

int storeCounter(ifstream&);

void readAndStoreFile(ifstream&, string&, string&, float&, unsigned&, unsigned&, HotDogStandsClass *, int);

void printStand(HotDogStandsClass*, int);

int transactionCounter(ifstream&);

void readTransaction(ifstream&, string, TransactionsClass* , int);

void transactionProcessor(HotDogStandsClass*, TransactionsClass*, int, int);

void updateFile(ofstream&, ofstream&, HotDogStandsClass*, int, string, string);


int main()
{
   string infoFileName = "InfoHotDogStands.txt",
          transactionsFileName = "InfoHotDogStandsTransactions.txt",
          globalSoldFileName = "InfoGlobalSold.txt";
   string id, address, infoStuff;
   float hotdogPrice;
   unsigned inventory, globalSold;
   ifstream info, sold, transactions;
   ofstream infoOutput , globalOutput;

   info.open(infoFileName);

   if(info)
   {
      int standCounter = storeCounter(info);
      HotDogStandsClass* standPtr = new HotDogStandsClass[standCounter];
     
      info.open(infoFileName);
      readAndStoreFile(info, id, address, hotdogPrice, inventory, globalSold , standPtr, standCounter);

      sold.open(globalSoldFileName);
      if (sold)
      {
         sold >> globalSold;
         standPtr[0].globalSoldCountUns = globalSold;

         printStand(standPtr, standCounter);
         transactions.open(transactionsFileName);
         if (transactions)
         {
            int operationCounter = transactionCounter(transactions);
            TransactionsClass* transactionPtr = new TransactionsClass[operationCounter];

            transactions.open(transactionsFileName);
            readTransaction(transactions, transactionsFileName, transactionPtr, operationCounter);
            transactionProcessor(standPtr, transactionPtr, standCounter, operationCounter);
            updateFile(infoOutput, globalOutput, standPtr, standCounter, infoFileName, globalSoldFileName);

         }
         else
         {
            cout << transactionsFileName << " could not be opened\n";
         }
      }
      else
      {
         cout << globalSoldFileName << " could not be opened\n";
      }
      

      
   }
   else
   {
      cout <<infoFileName << " could not be opened\n";
   }

  return 0;
}






















int storeCounter(ifstream& infoFile)
{
   string store;
   int count = 0;
   
   while (getline(infoFile, store, '\n'))
   {
      count++;
   }
   infoFile.close();

   return count;
}


void readAndStoreFile(ifstream& infoFile, string& id, string& address, float& price, unsigned& inventory, unsigned& globalsold, HotDogStandsClass *ptr, int standCount)
{
   string priceStr, inventoryStr, globalSoldStr;
   int count = 0;
   while (getline(infoFile, id, ',') &&  count < standCount)
   {
      getline(infoFile, address, ',');
      getline(infoFile, priceStr, ',');
      getline(infoFile, inventoryStr, ',');
      getline(infoFile, globalSoldStr, '\n');

      price = atof(priceStr.c_str());
      inventory = atoi(inventoryStr.c_str());
      globalsold = atoi(globalSoldStr.c_str());

      ptr[count].setIdStr(id);
      ptr[count].setAddressStr(address);
      ptr[count].setPriceF1(price);
      ptr[count].setInventoryAmountUns(inventory);
      ptr[count].setSoldAmountUns(globalsold);
      count++;
   }
}

void printStand(HotDogStandsClass* ptr,int standCount)
{
   cout << "Intial states of stands:\n";
   cout << "===========================\n\n";
   
   for (int count = 0; count < standCount; count++)
   {
      cout << ptr[count] << endl;
      
   }

   cout << "Global sold: " << ptr[2].globalSoldCountUns << endl << endl;
   cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
}

int transactionCounter(ifstream& transactionFile)
{
   string transaction;
   int count = 0;

   while (getline(transactionFile, transaction, '\n'))
   {
      count++;
   }
   transactionFile.close();

   return count;
}

void readTransaction(ifstream& transactionFile, string fileName, TransactionsClass *transactionPtr, int transactionCounter)
{
   string stand, action, amountStr;
   unsigned amount;
   int count = 0;
   while (getline(transactionFile, stand, ',') && count < transactionCounter)
   {
      getline(transactionFile, action, ',');
      getline(transactionFile, amountStr, '\n');
      amount = atoi(amountStr.c_str());
      transactionPtr[count].setIdentifcationStr(stand);
      transactionPtr[count].setTransactionIdStr(action);
      transactionPtr[count].setTransactionArgumentUns(amount);
      count++;
   }
}

void transactionProcessor(HotDogStandsClass* standPtr, TransactionsClass* transactionPtr, int standCount, int transactionCount)
{
   cout << "Process Transactions:\n";
   cout << "=====================\n\n";
   for (int tranCount = 0; tranCount < transactionCount; tranCount++)
   {
      for (int stdCount = 0; stdCount < standCount; stdCount++)
      {
         if (transactionPtr[tranCount].getIdentifcationStr() == standPtr[stdCount].getIdStr())
         {
            cout << "---------------------\n\n";
            cout << "HotDog Stand Current Status:\n\n";
            cout << standPtr[stdCount];
            cout << "Transaction:\n\n";
            cout << "Transaction Stand Id: " << transactionPtr[tranCount].getIdentifcationStr() << endl;
            cout << "Transaction Id      : " << transactionPtr[tranCount].getTransactionIdStr() << endl;
            cout << "Transaction Argument: " << transactionPtr[tranCount].getTransactionArgumentUns() << endl << endl;
            if (transactionPtr[tranCount].getTransactionIdStr() == "stock inventory")
            {
               standPtr[stdCount].stockInventoryAmountUns(transactionPtr[tranCount].getTransactionArgumentUns());
            }
            else if (transactionPtr[tranCount].getTransactionIdStr() == "buy")
            {
               standPtr[stdCount].hotDogsBuyUns(transactionPtr[tranCount].getTransactionArgumentUns());
            }

            cout << "HotDog Stand Status After Transaction: \n\n";
            cout << standPtr[stdCount] << endl;
            cout << "Global Sold: " << standPtr[stdCount].globalSoldCountUns << endl << endl;


            cout << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
            break;
         }
      }
      
   }

   printStand(standPtr, standCount);
}


void updateFile(ofstream& infoFile, ofstream& globalFile, HotDogStandsClass* ptr, int standCount, string fileName, string globalFileName)
{
   infoFile.open(fileName);
   globalFile.open(globalFileName);
  
   if (infoFile)
   {
      for (int count = 0; count < standCount; count++)
      {
         infoFile << ptr[count].getIdStr() << ',' << ptr[count].getAddressStr() << ',' << ptr[count].getPriceF1() << ','
                  << ptr[count].getInventoryAmountUns() << ',' << ptr[count].getSoldAmountUns() << endl;

         
      }

      globalFile << ptr[standCount - 1].globalSoldCountUns;
   }
}
