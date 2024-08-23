//Pranav Joseph paj220001

#include <chrono>
#include <limits>
#include <locale>
#include <stdio.h>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace chrono;

template <class TypeMultiply>
bool isSafeMultiply(TypeMultiply mult01, TypeMultiply mult02, TypeMultiply& multResult) {

   bool safe = false;
   /*$$
   add code to check if mult01 or mult02 = 0
   if so, set multResult to 0 and leave with a true
   */

   if (mult01 == 0 || mult02 == 0)
   {
      multResult = 0;
      safe = true; 
      return safe;
   }

   /*$$
   calculate the multResult from mult01 and mult02
   check if mult01 is equal to the multResult divided by mult02
   if mult01 is equal to the multResult divided by mult02 then leave with a true
   if not equal then leave with a false
   */

   multResult = mult02 * mult01;
   if (mult01 == multResult / mult02)
   {
      safe = true;
      return safe;
   }
   else
      return safe;

}
template <class TypeMultiply>
void calculateTimeFactorialLoopFunc(void) {

   //$$ set time start to clock now() 
   auto timeStart = steady_clock::now();


   TypeMultiply multiplier = 1,
      factorialResult = 1;

   while (isSafeMultiply(multiplier, factorialResult, factorialResult))
   {
      // display the multiplier and the factorialresult using field wdths of 3 and 27 respectively
      // increment the multiplier
      cout << setw(3) << multiplier << setw(27) << factorialResult << endl;
      multiplier++;
   }

   // calculate timeElapsed as described in the assignment
   auto timeElapsed = duration_cast<nanoseconds> (steady_clock::now() - timeStart);


   cout << endl;
   /*$$
   Display "Unsigned overflow at : " using setw() to display multiplier
   Display "Time Elapsed (nano)  : " using setw() to display timeElapsed.count()
   */

   cout << "Unsigned overflow at : " << setw(20) << multiplier << endl;
   cout << "Time Elapsed (nano)  : " << setw(20) << timeElapsed.count() << endl;

}//calculateTimeFactorialLoopFunc

 //------------------------------------------
template <class TypeMultiply>
void factorialRecursiveFunc(TypeMultiply& multiplier, TypeMultiply factorialResult) {

   if (isSafeMultiply(multiplier, factorialResult, factorialResult)) {
      cout << setw(3) << multiplier << setw(27) << factorialResult << endl;
      //$$ invoke factorialRecursiveFunc with ++multiplier and factorialResult
      factorialRecursiveFunc <TypeMultiply>(++multiplier, factorialResult);
   }
   return;

}//factorialRecursive

 //------------------------------------------  
template <class TypeMultiply>
void calculateTimeFactorialRecursiveFunc() {

   //$$ set time start to clock now() 
   auto timeStart = steady_clock::now();

   TypeMultiply mult01 = 1;
   factorialRecursiveFunc <TypeMultiply>(mult01, 1);

   // calculate timeElapsed as described in the assignment
   auto timeElapsed = duration_cast<nanoseconds> (steady_clock::now() - timeStart);


   cout << endl;
   /*$$
   Display "Unsigned overflow at : " using setw() to display multiplier
   Display "Time Elapsed (nano)  : " using setw() to display timeElapsed.count()
   */

   cout << "Unsigned overflow at : " << setw(20) << mult01 << endl;
   cout << "Time Elapsed (nano)  : " << setw(20) << timeElapsed.count() << endl;

}//calculateTimeFactorialRecursiveFunc()

template <typename TYPESIZE>
class FactorialCalculationClass {

private:
   unsigned typeSizeBits;

public:
   // Constructor
   FactorialCalculationClass(unsigned typeSize) {
      //$$ set typeSizeBits to typeSize;

      typeSizeBits = typeSize;
   }

   void executeFactorialForType() {

      cout <<
         typeSizeBits <<
         " bit unsigned Factorial Loop" << endl <<
         "------------------------------" << endl;
      calculateTimeFactorialLoopFunc <TYPESIZE>();
      cout << endl << endl;

      cout <<
         typeSizeBits <<
         " bit unsigned Factorial Recursion" << endl <<
         "-----------------------------------" << endl;
      calculateTimeFactorialRecursiveFunc <TYPESIZE>();
      cout << endl << endl;

   }

};// template <class TYPESIZE> class factorialCalculationClass

int main() {
   // condition cout set to local digit separation comas (USA)
   cout.imbue(locale("en_US"));

   

   /*$$
   create an object of FactorialCalculationClass <uintnn_t> called factorialCalculateUintnnObj(nn)
   where nn is the size in bits for the tempalte type uintnn_t, the object name
   factorialCalculateUintnnObj and the nn for the argument (nn) to the constructor
   nn must equal nn = 16, 32 and 64 to make the 3 objects
   */

   int nn[] = { 16, 32, 64 };
   FactorialCalculationClass <uint16_t> factorialCalculateUint16Obj(nn[0]);
   FactorialCalculationClass <uint32_t> factorialCalculateUint32Obj(nn[1]);
   FactorialCalculationClass <uint64_t> factorialCalculateUint64Obj(nn[2]);

   /*$$
   for each of the 3 nn objects factorialCalculateUintnnObj
   invoke the executeFactorialForType()
   */
   factorialCalculateUint16Obj.executeFactorialForType();
   factorialCalculateUint32Obj.executeFactorialForType();
   factorialCalculateUint64Obj.executeFactorialForType();

   /*$$
     display Press enster key once or twice to end and hold th screen
     */
   cout << "Press the enter key once or twice to end..." << endl; cin.ignore(); cin.get();


   return 0;
}
