
#include <iostream>
#include <iomanip>
#include "Seller.h"
#include <cstring>

using namespace std;

/****************************************************************

   FUNCTION:   Seller

   ARGUMENTS:  No arguments

   RETURNS:    No return

   NOTES:      The function is a default constructor.
		which doesnt have to set the variables but it does set them to zeros
****************************************************************/

	Seller::Seller()
	{
		salesTotal = 0;

	}

/****************************************************************

   FUNCTION:   Seller

   ARGUMENTS:  Two arguments a name and a double for a sale amount

   RETURNS:    No return

   NOTES:      This constructor creates a new object with the input date. The data is a name and a double
		the double will consists of the sellers sales amount. 
****************************************************************/

	Seller::Seller(const char* newName , double newSales)
	{
		strcpy(name, newName);	//copies the arguments information into the objects variable name

		salesTotal = newSales;	// sets the argument data of double to the objects salestotal variable

	}


/****************************************************************

   FUNCTION:   getName

   ARGUMENTS:  No arguments

   RETURNS:    A const char with the name of the object

   NOTES:      This is a getter method. It keeps the task simple, that is to 
		get the objects name and return it to where its being called from. 
		it take no arguments bacause it doesnt need data to accomplished its task. 
****************************************************************/
	const char* Seller::getName() const
	{
		return name; // return the variable name of the object
	}

/****************************************************************

   FUNCTION:   getSalesTotal

   ARGUMENTS:  No Arguments

   RETURNS:    a double with the salesamount of the object

   NOTES:      This is a getter method. It keeps the task simple that is to
		get the objects sales amount double and return it to where its being called from.
		it takes no arguments because its doesnt need data to accoplished its taks.
****************************************************************/
	double Seller::getSalesTotal() const
	{
		return salesTotal;	//return a double salesAmount for an object
	}



/****************************************************************

   FUNCTION:   setSalesTotal

   ARGUMENTS:  a double

   RETURNS:    no return

   NOTES:      This is a setter method. It keeps the task simple that is to
                get the set the  sales amount as a  double for the especific object.
                The argument that it takes is the new value for the object.
****************************************************************/

	void Seller::setSalesTotal(double newSales)
	{
		salesTotal = newSales;	  
	}

/****************************************************************

   FUNCTION:   print

   ARGUMENTS:  no arguments

   RETURNS:    no return

   NOTES:      This method is a print method. What it does it outputs the things we program it to display
		in this case we print the objects name and salesamount. We use cout to send information to the screen to display.
		we set indentations for the name and spacing for the number so it can be display in a column form. 
****************************************************************/

	void Seller::print()const 
	{
	 cout << left << setw(30)<< name << right<<setw(9)<<  setprecision (2) << fixed << salesTotal<<endl;
	}





