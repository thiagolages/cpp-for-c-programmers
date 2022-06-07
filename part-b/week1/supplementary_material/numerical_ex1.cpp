//Ira Pohl  Numerical Algorithms Module for lecture 1.13
//C++ For C Programmers Part B
//April 2016
#include <iostream>
#include <numeric> // previously <algorithm>
using namespace std;

int main()
{
   double v1[3] = { 1.0, 2.5, 4.6 },
          v2[3] = { 1.0, 2.0, -3.5 };
   double sum, inner_p;

   //v1 and v2 are base addresses - so they can be used as
   //the beginning of an iterator range
   //v1 + 3 is pointer arithmetic and is the end sentinel.

   sum = accumulate(v1, v1 + 3, 0.0);
   inner_p = inner_product(v1,  v1 + 3, v2, 0.0);
   cout << "sum = " << sum 
        << ",   product = " << inner_p 
        << endl;
}

