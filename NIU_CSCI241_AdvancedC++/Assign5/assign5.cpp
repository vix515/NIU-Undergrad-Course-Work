/********************************************************************
   PROGRAM:    CSCI 241 Assignment 5
   PROGRAMMER: Victor Padilla
   LOGON ID:   Z1689628
   DUE DATE:   10/27/2015

   FUNCTION:   In this assignment we will create a dynamic array
		and work with techniques to manage dynamically-allcoated
		storage in c++. We will have to set up arrays with no variables
		(epmty arrays).We will add data to the data array and copy too.
		Create new array from other arrays and compare their values aswell.
*********************************************************************/

#include <iostream>
#include "Vector.h"

using std::cout;
using std::endl;

int main()
   {
   cout << "Testing default constructor\n\n";

   Vector v1;								//Creating a default object with no parameters

   cout << "v1: " << v1 << endl;					//printing put object v1
   cout << "v1 size: " << v1.size() << endl;				//printing v1's size
   cout << "v1 capacity: " << v1.capacity() << endl;			//printing v1's capacity size
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking whether v1 is empty or not
   cout << endl;

   cout << "Testing push_back()\n\n";

   for (int i = 10; i < 200; i+= 10)					//pushing variables into the object
      v1.push_back(i);							//its adding integers to its current free location

   cout << "v1: " << v1 << endl;   					//printing out v1
   cout << "v1 size: " << v1.size() << endl;				//printing out size of v1
   cout << "v1 capacity: " << v1.capacity() << endl;			//printing out v1's capacity
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking whether v1 is empty or not
   cout << endl;

   cout << "Testing pop_back()\n\n";

   for (int i = 0; i < 3; ++i)
      {									//going through the foor loop three times
      v1.pop_back();							//calling the funtion pop_back
      }									//and its doing its process 3 times

   cout << "v1: " << v1 << endl;   					//printing v1 after going through pop_back
   cout << "v1 size: " << v1.size() << endl;				//printing v1's size
   cout << "v1 capacity: " << v1.capacity() << endl;			//printing v1's capacity
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking too see if object is empty
   cout << endl;

   cout << "Testing copy constructor()\n\n";

   Vector v2 = v1;							//creating a new object with same values as old object

   cout << "v1: " << v1 << endl;   					//printing out the original object
   cout << "v1 size: " << v1.size() << endl;				//printing original object's size
   cout << "v1 capacity: " << v1.capacity() << endl;			//printing original object's capacity
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking to see if the original object is empty
   cout << endl;

   cout << "v2: " << v2 << endl;   					// an independent copy of the original object is now being printed
   cout << "v2 size: " << v2.size() << endl;				//v2's size is being printed
   cout << "v2 capacity: " << v2.capacity() << endl;			//v2's capacity is being printed
   cout << "v2 is " << ((v2.empty()) ? "empty\n" : "not empty\n");	//checking to see if v2 is empty
   cout << endl;

   cout << "Testing front() and back()\n\n";

   cout << "Front item of v1: " << v1.front() << endl;			//displaying the first element in object v1 calling the front function
   cout << "Front item of v2: " << v2.front() << endl << endl;		//displaying the first element in object v2 calling the front function

   cout << "Rear item of v1: " << v1.back() << endl;			//displaying the last element in object v1 calling the back function
   cout << "Rear item of v2: " << v2.back() << endl << endl;		//displaying the last element in object v2 calling the back function

   cout << "v1: " << v1 << endl;   					//displaying object v1
   cout << "v1 size: " << v1.size() << endl;				//displaying object v1's size
   cout << "v1 capacity: " << v1.capacity() << endl;			//displaying object v1's capacity
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking to see if object v1 is empty
   cout << endl;

   cout << "v2: " << v2 << endl;   					//displaying object v2
   cout << "v2 size: " << v2.size() << endl;				//displaying object v2's size
   cout << "v2 capacity: " << v2.capacity() << endl;			//displaying object v2's capacity
   cout << "v2 is " << ((v2.empty()) ? "empty\n" : "not empty\n");	//checking to see if object v1 is empty
   cout << endl;

   cout << "Testing pop() to empty\n\n";

   while (!v1.empty())
      {									//this while loop will continue running until v1 is empty
      cout << v1.back() << ' ';						//it will start displaying the elements on v1 backwards
      v1.pop_back();
      }

   cout << endl;
   cout << "v1 size: " << v1.size() << endl;				//v1 size will be display
   cout << "v1 capacity: " << v1.capacity() << endl;			//v1 capacity will be display
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");	//checking if v1 is empty
   cout << endl;

   cout << "Testing copy assignment operator\n\n";

   Vector v3;								//creating an empty object with no parameters

   v3 = v2;								//copying elements and variable from v2 to v3

   cout << "v2: " << v2 << endl;   					//displaying v2
   cout << "v2 size: " << v2.size() << endl;				//displaying  v2's size
   cout << "v2 capacity: " << v2.capacity() << endl;			//displaying v2's capacity
   cout << "v2 is " << ((v2.empty()) ? "empty\n" : "not empty\n");	//checking to see if v2 is empty
   cout << endl;

   cout << "v3: " << v3 << endl;   					//displaying v3
   cout << "v3 size: " << v3.size() << endl;				//displaying v3's size
   cout << "v3 capacity: " << v3.capacity() << endl;			//displaying v3's capacity
   cout << "v3 is " << ((v3.empty()) ? "empty\n" : "not empty\n");	//checking to see if v3 is empty
   cout << endl;

   Vector v4;								//creating vector v4

   v3 = v4;								//copying v4 to v3

   cout << "v3: " << v3 << endl;   					//displaying v3, its size, its capacity and it will check too see if its empty
   cout << "v3 size: " << v3.size() << endl;
   cout << "v3 capacity: " << v3.capacity() << endl;
   cout << "v3 is " << ((v3.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "v4: " << v4 << endl;   					//displaying v4, its size, its capacity and it will check to see if its empty
   cout << "v4 size: " << v4.size() << endl;
   cout << "v4 capacity: " << v4.capacity() << endl;
   cout << "v4 is " << ((v4.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   v3 = v2;								//copying v2 to v3

   cout << "v3: " << v3 << endl;   					//displaying v3, its size, its capacity, and it will check to see if its empty
   cout << "v3 size: " << v3.size() << endl;
   cout << "v3 capacity: " << v3.capacity() << endl;
   cout << "v3 is " << ((v3.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing clear()\n\n";

   v2.clear();								//calling the clear method of v2 which will set its size to 0

   cout << "v2 (size " << v2.size() << "): " << v2 << endl;		//displaying the size of v2 and printing its elements
   cout << "v3 (size " << v3.size() << "): " << v3 << endl << endl;	//displaying the size of v3 and printing its elements

   cout << "Testing assignment to self and swap\n\n";

   v3 = v3;								//copying v3 to v3
   v2 = v3;								//copying v3 to v2
   v3.clear();								//calling the clear method of v3 to change its size to 0

   cout << "v2 (size " << v2.size() << "): " << v2 << endl;		//displaying the size of v2 and printing its elements
   cout << "v3 (size " << v3.size() << "): " << v3 << endl << endl;	//displaying the size of v3 and printing its elements

   cout << "Testing chained assignment\n\n";

   Vector v5;								//creating empty object v5

   v5 = v3 = v2;							//copying v2 to v3 and then v3 to v5

   cout << "v2 (size " << v2.size() << "): " << v2 << endl;		//displaying the size and elements of v2, v3 and v5
   cout << "v3 (size " << v3.size() << "): " << v3 << endl;
   cout << "v5 (size " << v5.size() << "): " << v5 << endl << endl;

   cout << "Testing write version of subscript operator\n\n";

   for (size_t i = 0; i < v5.size(); ++i)				//this for loop will run for as long as the size of the object
      v5[i] += 5;							//it will increment each of the object's elements by 5

   cout << "v5 (size " << v5.size() << "): " << v5 << endl << endl;   	//displaying v5's size and its elements

   cout << "Testing read version of subscript operator\n\nv5: ";

   for (size_t i = 0; i < v5.size(); ++i)				//displaying the elements in v5 one by one with a for loop
      cout << v5[i] << ' ';
   cout << endl << endl;

   cout << "Testing const correctness\n\n";

   const Vector& r5 = v5;						//create a conts object with the equality of v5

   cout << "v5: " << r5 << endl;   					//v5 is = to r5 so print out r5 and make it look like v5
   cout << "v5 size: " << r5.size() << endl;				//since theyre are equal we can print out their size and there is no difference
   cout << "v5 capacity: " << r5.capacity() << endl;			//same with their capacity
   cout << "v5 is " << ((r5.empty()) ? "empty\n" : "not empty\n");	//and the emptiness
   cout << "Front item of v5: " << r5.front() << endl;			// their first item
   cout << "Rear item of v5: " << r5.back() << endl;			// and last
   cout << "4th item of v5: " << r5[3] << endl << endl;			//as well as any other element. r5 and v5 are absolutely equal.

   v1 = r5;

   cout << "v1: " << v1 << endl;					//v1 is now equal to r5 which is v5
   cout << "v1 size: " << v1.size() << endl;				//displaying v1's size and checking for emptiness
   cout << "v1 is " << ((v1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing equality operator\n\n";

   cout << "v1 and v5 are " << ((v1 == r5) ? "equal\n" : "not equal\n");	//checking to see if objects are equal
   cout << "v5 and v3 are " << ((r5 == v3) ? "equal\n" : "not equal\n");
   cout << "v1 and v2 are " << ((v1 == v2) ? "equal\n" : "not equal\n");
   v5.pop_back();								//calling v5 pop_back method
   cout << "v1 and v5 are now " << ((v1 == v5) ? "equal\n" : "not equal\n");	//checking equality
   cout << endl;

   //
   // Extra Credit
   //
   // This code will call the move constructor and move assignment
   // operator if they exist.
   //
   // If those move semantics methods are not implemented, this code
   // will call the copy constructor and copy assignment operator
   // instead. The output will be different in that case.
   //
   cout << "Extra Credit: Testing move constructor\n\n";

   Vector v6 = std::move(v5);

   cout << "v6: " << v6 << endl;
   cout << "v6 size: " << v6.size() << endl;
   cout << "v6 is " << ((v6.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "v5: " << v5 << endl;
   cout << "v5 size: " << v5.size() << endl;
   cout << "v5 is " << ((v5.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Extra Credit: Testing move assignment operator\n\n";

   v5 = std::move(v6);

   cout << "v5: " << v5 << endl;
   cout << "v5 size: " << v5.size() << endl;
   cout << "v5 is " << ((v5.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "v6: " << v6 << endl;
   cout << "v6 size: " << v6.size() << endl;
   cout << "v6 is " << ((v6.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   return 0;
   }
