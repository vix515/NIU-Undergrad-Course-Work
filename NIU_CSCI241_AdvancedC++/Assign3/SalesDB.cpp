#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "SalesDB.h"
#include <string.h>
using namespace std;

/****************************************************************

   FUNCTION:   SalesDB

   ARGUMENTS:  no arguments is a default contructor which takes no arguments to create an object

   RETURNS:    Nothing it only creates the object

   NOTES:      The default constructor is mandatory in every class. It will take no parameters and set and object to a default state
		In this case the parameter does not set any type of information to the object.
****************************************************************/
	SalesDB::SalesDB()
	{
		//null constructor can be empty
	}

/****************************************************************

   FUNCTION:   SalesDb

   ARGUMENTS:  A const char that will take a list of sales and pass it to  functions

   RETURNS:    nothing

   NOTES:      This constructor will take the argument (which is a file) and open it.
		It will then convert the information, seperate it and send to an object.
		An object array is already declare with 3 sections containing 6  objects and thats where the data will be send.
		we made sure the file was open in case of any error. and we closed it at the end.
****************************************************************/
	SalesDB::SalesDB(const char* workers)
	{
		ifstream inFile;			//create a variable for a file
		inFile.open(workers, ios::binary);	//open the file
		assert(inFile);				//make sure the file opened

		inFile.read((char*) this, sizeof(SalesDB));	//send the information to the corresponding variable to hold the information
		inFile.close();					//make sure to close the file bedore leaving the method
	}

/****************************************************************

   FUNCTION:   print

   ARGUMENTS:  none

   RETURNS:    nothing but it does output to the screen.

   NOTES:      This method when called, it will print out one object at a time for all the regions in the array created by the contructor.
		it has a loop to make a repetative action ,of printing an object's information, easier.
		It will print out the name and sales amount of the object. It has a header which is set to display information in columns.
		Because the original array is a 2-d array we create two for loops. Which first go through the rows of the array and secondly
		go through the column of the array. That way searching by category and object (region and seller)
****************************************************************/
	void SalesDB::print()const
	{
		string region[3]={"Eastern Region", "Midwestern Region", "Western Region"};	//will give names to the groupings of the sellers
		cout<<"Sales DataBase Listing"<<endl<<endl;					//header for the output
		for( int i=0 ; i < 3; i++)							//start of a for loop to search thru groupings
		{
			cout<<"\n"<<region[i]<<endl<<endl;					//give a name to the groupings
			cout<<left<<setw(30)<<"Name"<<left<<setw(10)<<"Sales"<<endl<<endl;	//header for columns

			for(int j=0 ; j < 6; j++)						//for lopp to search through array and find the sellers
			{
				object[i][j].print();						//call the object's prnt method
			}
		}
	}

/****************************************************************

   FUNCTION:   processSalesData

   ARGUMENTS:  A list send through main.

   RETURNS:    Nothing

   NOTES:     This method will process data send to it trough a file. It will read and save the data with variables and then use the variables to
		store the data accordingly with a loop. It will match the corresponing seller and update its Sales Amount with the new information.
****************************************************************/
	void SalesDB::processSalesData(const char* salesData)
	{

		ifstream inFile;	//variable to hold file
		int region;		//variable to hold an integer  region for the array
		int seller;		//variable to hold an interger seller for the array
		double  salesAmount;	//will set up a sales nubmer
		inFile.open(salesData);	//open file
		assert(inFile);		//make sure the file opens


		inFile >> region;	//sent the first piece of information ans store it in region


		while(!inFile.eof())		//This loop will go trough the code until it reaches the end of the file
		{
			inFile >>seller;	//sent the next piece of information of the file and store it in 'seller'
			inFile >>salesAmount;	//sent the next piece of information of the file and store it in 'salesAmount'

			object[region][seller].setSalesTotal(salesAmount + object[region][seller].getSalesTotal());
						//the above sets up the new salesTotal for the object at indexed

			inFile >> region;	//restart the process of gathering data from the file
		}

		inFile.close();			//close the file before exiting
	}
