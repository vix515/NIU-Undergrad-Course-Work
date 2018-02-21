#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "SalesDB.h"
#include <string.h>
using namespace std;

/****************************************************************

   FUNCTION:   SalesDB

   ARGUMENTS:
	 No arguments, is a default constructor which takes no arguments to create an object

   RETURNS:
	 Nothing it only creates the object

   NOTES:
	 The default constructor is mandatory in every class. It will take no parameters and set and object to a default state. In this case the parameter does not set any type of information to the object.
****************************************************************/
	SalesDB::SalesDB()
	{
	}

/****************************************************************

   FUNCTION:
	 SalesDb

   ARGUMENTS:
	 A const char that will take a list of sales and pass it to  functions

   RETURNS:
	 nothing

   NOTES:
	 This contructor will take the argument (whic is a file) and open it with binary.
		It will then convert the information, seperate it and send to an object.
		An object array is already declare with 30 objects and thats where the data will be send.
		we made sure the file was open in case of any error. and we closed it at the end.
****************************************************************/
	SalesDB::SalesDB(const char* workers)
	{
		ifstream inFile;
		inFile.open(workers, ios::binary);
		assert(inFile);

		inFile.read((char*) this, sizeof(SalesDB));
		inFile.close();
	}

/****************************************************************

   FUNCTION:
	 print

   ARGUMENTS:
	 none

   RETURNS:
	 nothing but it does output to the screen.

   NOTES:
	 This method when called. It will print out one object at a time for all the object in the array create by the contructor. It has a loop to make a repetative action ,of printing an object's information, easier. It will print out the name and sales maount of the object. It has a header which is set to display information in columns.
****************************************************************/
	void SalesDB::print()
	{
		cout<<"Sales DataBase Listing"<<endl<<endl;
		cout<<left<<setw(30)<<"Name"<<left<<setw(10)<<"Sales"<<endl<<endl;
		for( int i=0 ; i < amount; i++)
		object[i].print();
	}

/****************************************************************

   FUNCTION:
	 sortSeller

   ARGUMENTS:
	 NONE

   RETURNS:
	 nothing

   NOTES:
	 This method when called will rearrange all the object in alphabetical order based on their name. It will compare in a loop the names and use the strcmp() to allowed it to define where the objects go in order.

****************************************************************/
	void SalesDB::sortSellers()
        {
   		int i, j; // intergers to use in the loop inignificant to the program as a whole just needed withinh the method.
   		Seller bucket; // creates a place holder for an object

   		for (i = 1; i < amount; i++)
      		{
      			bucket = object[i];

	      		for (j = i; (j > 0) && (strcmp(object[j-1].getName(), bucket.getName()) > 0); j--)
         		object[j] = object[j-1];

      			object[j] = bucket;
      		}
   	}

/****************************************************************

   FUNCTION:
	 serachforseller

   ARGUMENTS:
	 It recieves a string

   RETURNS:
	 Return and integer regarding the postion of the seller it found

   NOTES:
	 This method recieves a string and uses the strcmp() to check if it exists as an object. If it does it will return the index of where the seller is located in the array of seller. It does its search in binary mode which creates a simpler way to search by cutting in halves.
****************************************************************/
	int  SalesDB::searchForSeller(const char* name) const
	{
		int low = 0;// lower limit to search
   		int high = amount - 1; // to set its higher limit
   		int mid;// middle of the list to start a binary search

   		while (low <= high)//loop will allow the binary to choose which half to pick and then cut the next in hlaf and so on.
      		{
      			mid = (low + high) / 2;

      			if (strcmp(name, object[mid].getName()) == 0)
         		{
				return mid;
			}
      			if (strcmp(name, object[mid].getName()) < 0)
         			high = mid - 1;
      			else
        			 low = mid + 1;
      		}

   			return -1;	// if no real return is available then send a number of which we will recognize the outcome
	}

/****************************************************************

   FUNCTION:
	 processSalesData

   ARGUMENTS:
	 a list

   RETURNS:
	 nothing

   NOTES:
	 This method will take in a list of workers and transfers is sales to current sellers already created. It uses the searchforseller method to see if the lists contains all objects, then is sets the old Salestotal to new one.
****************************************************************/
	void SalesDB::processSalesData(const char* salesData)
	{

		ifstream inFile;
		char lastName[21];	//will set up a last name
		char firstName[11];	//will set upa firsrt name
		double  salesAmount;	//will set up a sales nubmer
		char name[31];		// will be a cobination of last name and first name

		inFile.open(salesData);
		assert(inFile);


		inFile >> lastName;	//set up last name

		cout<<"Sales Transactions"<<endl<<endl;
		while(!inFile.eof())
		{
			inFile >>firstName;	//sets up first name
			inFile >>salesAmount;	//gives a number to salesAmount

			strcpy (name, lastName);//will set the first part of the name
			strcat (name, ", ");	//adds a coma after the lastname
			strcat (name, firstName);//adds	firstname and creates a full name
			int index = searchForSeller(name);	//goes through the seller list and gets its location
			if(index == -1)				// to check if it doesnt exits
				cout<< "There is not such name"<<endl;
			else
			{
				cout<< name <<" "<< salesAmount << endl;
				object[index].setSalesTotal(salesAmount + object[index].getSalesTotal());//sets up the new salesTotal for the object at indexed
			}
			inFile >> lastName;
		}
			inFile.close();
	}
