//this file is used to define some functions of the HotDogStandClass like the operator overload which allows us to print out the whole summary
//just using 1 line of code. It also has the hotDogsBuyUns function which is used to update the info of a hotdog stand once a transaction occurs 

#ifndef HOTDOG_STAND_CLASS_CPP
#define HOTDOG_STAND_CLASS_CPP

#include "HotDogStandsClass.h"

using namespace std;

unsigned HotDogStandsClass::globalSoldCountUns = 0;

ostream& operator<<(ostream& strm, const HotDogStandsClass &obj)
{
   cout << fixed << showpoint << setprecision(2);
   strm << "Stand Id   : " << obj.getIdStr() << endl;
   strm << "Address    : " << obj.getAddressStr() << endl;
   strm << "Price      : " << obj.getPriceF1() << endl;
   strm << "Inventory  : " << obj.getInventoryAmountUns() << endl;
   strm << "Store Sold : " << obj.getSoldAmountUns() << " at $" << obj.getPriceF1() << " ea.\n\n";
   return strm;
}


void HotDogStandsClass::hotDogsBuyUns(unsigned count)
{
   if (inventoryAmountUns > 0)
   {
      if (count <= inventoryAmountUns)
      {
         inventoryAmountUns -= count;
         soldAmountUns += count;
         globalSoldCountUns += count;
      }
      else
      {
         cout << "*We only have " << inventoryAmountUns << " hotdogs left.*\n\n";
      }
   }
   else
   {
      cout << "*There are not any more hotdogs left to be sold.*\n\n";
   }

}

#endif