//this is the definition of the HotDogStandsClass which can then be used to store all the information of the hot dog stand and update it when a 
//transaction occurs 

#ifndef HOTDOG_STAND_CLASS_H
#define HOTDOG_STAND_CLASS_H


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class HotDogStandsClass;

ostream& operator<<(ostream&, const HotDogStandsClass&);

class HotDogStandsClass
{
private:
   string identificationStr,
          addressStr;
   float  hotdogPriceF1;
   unsigned inventoryAmountUns,
            soldAmountUns;

public: 
   HotDogStandsClass()
   {
      this->identificationStr;
      this->addressStr;
      this->hotdogPriceF1;
      this->inventoryAmountUns;
      this->soldAmountUns;
   }

   static unsigned globalSoldCountUns;

   const string& getIdStr() const
   {
      return identificationStr;
   };

   void setIdStr(const string& identificationStr)
   {
      this->identificationStr = identificationStr;
   }

   const string& getAddressStr() const
   {
      return addressStr;
   }

   void setAddressStr(const string& addressStr)
   {
      this->addressStr = addressStr;
   }

   float getPriceF1() const
   {
      return hotdogPriceF1;
   }

   void setPriceF1(float hotdogPriceF1)
   {
      this->hotdogPriceF1 = hotdogPriceF1;
   }

   unsigned getSoldAmountUns() const
   {
      return soldAmountUns;
   };

   void setSoldAmountUns(unsigned soldAmountUns)
   { 
      this->soldAmountUns = soldAmountUns;
   }

   unsigned getInventoryAmountUns() const
   {
      return inventoryAmountUns;
   };

   void setInventoryAmountUns(unsigned inventoryAmountUns)
   { 
      this->inventoryAmountUns = inventoryAmountUns;
   }

   void stockInventoryAmountUns(unsigned stockCountUns)
   { 
      inventoryAmountUns += stockCountUns;
   }

   void hotDogsBuyUns(unsigned count);

   friend ostream& operator<<(ostream& strm, const HotDogStandsClass& obj);

};


#endif
