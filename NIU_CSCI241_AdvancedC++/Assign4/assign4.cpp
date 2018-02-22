/********************************************************************
   PROGRAM:    CSCI 241 Assignment 4
   PROGRAMMER: Victor Padilla
   LOGON ID:   z1689628
   DUE DATE:   10/15/15

   FUNCTION:
   This program tests the functionality of the Complex class.
   It will create a Complex object with initial arguments.
   This main method will also add objects and multiply them.
   It will also compare two objects and see if theyre equal.
   Changing the values of the objects is implemented here through various methods.
*********************************************************************/

#include <iostream>
#include <iomanip>
#include "Complex.h"

using std::cin;
using std::cout;
using std::endl;

int main()
   {
   cout << "Testing constructor... "; 	//Process Message
   Complex c1(23, 34);			//Creation of an object
   const Complex c4(3, 4);		//creation of an object

   cout << "done\n";  					//Process Message
   cout << "Testing default constructor use... ";	//Process Message

   Complex c2;						//Creation of an object with default values
   Complex c3;						//Creation of an object with default values

   cout << "done\n\n";							//Process Message
   cout << "Testing stream insertion operator and constructors...\n";	//Process Message

   cout << "c1 = " << c1 << endl;		//Printing of an object
   cout << "c2 = " << c2 << endl << endl;	//Printing of an object

   cout << "Testing get methods...\n";		//Process Message

   cout << "Real part of c4 = " << c4.getRealPart() << endl;		//Printing of the realpart in object c4 calling the getter
   cout << "Imaginary part of c4 = " << c4.getImaginaryPart() << endl;	//Printing of the imaginary number

   double r, i;							//declaration of intergers to modify for an object

   c4.getComplex(r, i);						//get method of an object with variables to set
   cout << "Real part of c4 = " << r << endl;			//printing of the real part
   cout << "Imaginary part of c4 = " << i << endl << endl;	//printing of the imaginary part

   cout << "Testing set methods...\n";				//Process Message

   c2.setComplex(3.7, 2.5);					//setting values of the object
   cout << "New value of c2 = " << c2 << endl;			//Printing of the new Values
   c2.setRealPart(-1.4);					//setting a new value real
   cout << "New value of c2 = " << c2 << endl;  		//pringing of value
   c2.setImaginaryPart(83);  					//setting new imaginary number
   cout << "New value of c2 = " << c2 << endl << endl;		//printing of new value

   cout << "Testing stream extraction operator...\n";		//process Message

   cout << "Enter a complex number in the form (a, b) ";	//Prompt for user
   cin >> c2;							//User input
   cout << "New value of c2 = " << c2 << endl << endl;		//Printing of values set by user

   cout << "Testing addition operator...\n";			//Process Message

   c3 = c1 + c4;						//Addition of object
   cout << "c3 = " << c3 << endl;				//New value of object after addition
   cout << c4 << " + " << c1 << " = " << c4 + c1 << endl;	//Priting of objects and their addtion result
   cout << c4 << " + " << c4 << " = " << c4 + c4 << endl << endl; //Printing of objects and their addition result

   cout << "Testing multiplication operator...\n";		//Process message

   c3 = c1 * c4;						//Multiplication of objects
   cout << "c3 = " << c3 << endl;				//printing of new object after multiplication
   cout << c4 << " * " << c1 << " = " << c4 * c1 << endl;  	//printing of objects and their multiplication result
   cout << c4 << " * " << c4 << " = " << c4 * c4 << endl << endl; //Printing of objects and their multiplication result

   cout << "Testing equality operator...\n";			//process message

   cout << c1 << " and " << c3;					//Comparison of two objects
   (c1 == c3) ? cout << " are equal\n" : cout << " are not equal\n";	//Results of comparison

   const Complex c5(3, 4);					//Creation of new Object
   cout << c4 << " and " << c5;					//Comparison of objects
   (c4 == c5) ? cout << " are equal\n" : cout << " are not equal\n"; //result of comparison

   return 0;
   }
