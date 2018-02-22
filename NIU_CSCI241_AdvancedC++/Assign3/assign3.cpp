

/****************************************************************
   PROGRAM:   assign3
   AUTHOR:    Victor Padilla
   LOGON ID:  Z1689628  (your Z number here)
   DUE DATE:  9/29/2015

   FUNCTION:
   To create object (sellers) and set their sales amount
   This program takes a data file(salesDB) and will convert elements of information into objects.
	 These objects are known as sellers and each seller will have a double which represents its seller's sales gather from sales.txt
	 The information is gather and a 2-d array is created in which there are seller divided into regions.

   INPUT:
   salesDB, sales.txt.  This files provide the information that is require to create an object.


   OUTPUT:
   The Output is locally saved. It contains information about regional sales with the name of the seller and the sales amount.

   NOTES:
   The program is not linear. Meaning that is will depend on what it is that is needed to be done so the next step will occur.
	 Just like calling the print method at different times and its included even though it was already used.
****************************************************************/
#include <iostream>
#include "SalesDB.h"
#include "Seller.h"
using std::cout;
using std::endl;

int main()
   {
      const char* filename = "salesdb"; 	//have a variable with a filename ready
         SalesDB object(filename);		//create an object and send a file with the variable holding its name

	 object.print();			//calling the print method of the object
	 cout<<endl<<endl;			//create a new line
     	 const char* filename2 = "sales.txt";	//createa a second variable with a filename
	 object.processSalesData(filename2);	//Call on the objects method to process a new file which is send with a variable holding its name
	 cout<<endl<<endl;			//create a new line
	 object.print();			//calling the objects print method

      return 0;
   }
