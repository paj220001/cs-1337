//this file contains the transactions class which is used to store all the transactions read from the transactions file
//this can then be used in main to update the hot dog stand

#ifndef TRANSACTIONS_CLASS_CLASS_H
#define TRANSACTIONS_CLASS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TransactionsClass {

private:
   string   standIdentifcationStr;
   string   transactionIdStr;
   unsigned transactionArgumentUns;

public:
   const string& getIdentifcationStr() const
   {
      return standIdentifcationStr;
   };
   void setIdentifcationStr(string standIdentifcationStr)
   { 
      this->standIdentifcationStr = standIdentifcationStr;
   }

   const string& getTransactionIdStr() const
   {
      return transactionIdStr;
   };
   void setTransactionIdStr(string transactionIdStr)
   { 
      this->transactionIdStr = transactionIdStr;
   }

   unsigned getTransactionArgumentUns() const
   {
      return transactionArgumentUns;
   };
   void setTransactionArgumentUns(unsigned transactionArgumentUns)
   { 
      this->transactionArgumentUns = transactionArgumentUns;
   }

   friend ostream& operator<<(ostream& strm, const TransactionsClass& obj);

};

#endif
