

/****************************************************************
   PROGRAM:   Assigment2
   AUTHOR:    Victor Padilla

   FUNCTION:
   To create an object (sellers) and set their sales amount.
   This program takes a data file (salesDB) and will convert elements of information into objects.
	 This objects are known as sellers and each seller will have a number (double) which represents its seller's sales.
	 The list needs to be organized so we do an alphabetical order of workers with a function.
	 The workers will keep updating their sales as time progresses therefore adding a new file sales.txt
	 this file will make it through a function which will search for individual sellers and updated their sales anount.

   INPUT:
   salesDB, sales.txt.  This files provide the information that is require to create an object.


   OUTPUT:
   The output is local and is a list of old data with new input and updated list of sales amount for sellers.


****************************************************************/
#include <iostream>
#include "SalesDB.h"
#include "Seller.h"
using std::cout;
using std::endl;

int main()
   {
      const char* filename = "salesdb";
         SalesDB object(filename);

	 object.sortSellers();
	 object.print();
	 cout<<endl<<endl;
     	 const char* filename2 = "sales.txt";
	 object.processSalesData(filename2);
	 cout<<endl<<endl;
	 object.print();

      return 0;
   }
