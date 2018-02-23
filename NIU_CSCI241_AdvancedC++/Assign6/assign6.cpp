/****************************************************************
   PROGRAM:   Assignment 6
   AUTHOR:    Victor Padilla
   LOGON ID:  z1689628
   DUE DATE:  11-6-2015

   FUNCTION:  This assignment is an exercise in implementing the queue ADT using an array-based data structure.

   INPUT:     Queue.cpp Queue.h assign6.cpp

   OUTPUT:    A file testing different implementations towards
               array.

   NOTES:     This program will create arrays. It will sort through them
               it will point to its last digits and first.
               It will copy on array to the other, and create copies.
               It also tests for errors.
****************************************************************/

#include <iostream>
#include <stdexcept>
#include "Queue.h"

using std::cout;
using std::endl;
using std::underflow_error;

int main()
   {
   cout << "Testing default constructor\n\n";

   Queue q1;                                                        //Creation of an object with a default constructor

   cout << "q1: " << q1 << endl;                                    //Print out object
   cout << "q1 size: " << q1.size() << endl;                        //Print objects size
   cout << "q1 capacity: " << q1.capacity() << endl;                //print objects capacity
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");  //Checking to see if object is empty
   cout << endl;

   cout << "Testing push()\n\n";

   for (int i = 10; i < 80; i+= 10)                                 //looping through digits to insert into an object
      q1.push(i);

   cout << "q1: " << q1 << endl;                                    //Printing object
   cout << "q1 size: " << q1.size() << endl;                        //printing objects sizse
   cout << "q1 capacity: " << q1.capacity() << endl;                //printing objects capacity
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");  //checking to see if object is empty
   cout << endl;

   cout << "Testing pop()\n\n";

   for (int i = 0; i < 3; ++i)                                        //creaeting indexes to delete off the array
      {
      q1.pop();
      }

   cout << "q1: " << q1 << endl;                                      //printing object
   cout << "q1 size: " << q1.size() << endl;                          //printing objects size
   cout << "q1 capacity: " << q1.capacity() << endl;                  //printing objects capacity
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");    //checking to see of object is empty
   cout << endl;

   cout << "Testing wrap-around on push()\n\n";

   for (int i = 2; i <= 8; i+= 2)                                      //creating new ints to insert into the object
      q1.push(i);

   cout << "q1: " << q1 << endl;                                       //printing object's elements
   cout << "q1 size: " << q1.size() << endl;                           //priting objects size
   cout << "q1 capacity: " << q1.capacity() << endl;                   //printing objects capacity
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");      // checking to see if object is empty
   cout << endl;

   cout << "Testing wrap-around on pop()\n\n";

   for (int i = 0; i < 6; ++i)                                          //creating indexes to delete off object
      {
      q1.pop();
      }

   cout << "q1: " << q1 << endl;                                        //printing object elements, its size and its capacity.
   cout << "q1 size: " << q1.size() << endl;                            //also checking to see if its empty
   cout << "q1 capacity: " << q1.capacity() << endl;
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing queue resize on push()\n\n";

   for (int i = 5; i < 70; i+= 5)                                       //creating more int to insert to the array in the object
      q1.push(i);

   cout << "q1: " << q1 << endl;                                        //printing the object, its size and its capacity
   cout << "q1 size: " << q1.size() << endl;                            //also check if its empty
   cout << "q1 capacity: " << q1.capacity() << endl;
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing copy constructor()\n\n";

   Queue q2 = q1;                                                      //creating a copy

   cout << "q1: " << q1 << endl;                                       //printing objects elements, its size and its capacity
   cout << "q1 size: " << q1.size() << endl;                           //also checking to see if its empty
   cout << "q1 capacity: " << q1.capacity() << endl;
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "q2: " << q2 << endl;                                       //priting copy checking its size and its capacity
   cout << "q2 size: " << q2.size() << endl;                          //also checking to see if its empty
   cout << "q2 capacity: " << q2.capacity() << endl;
   cout << "q2 is " << ((q2.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing front() and back()\n\n";

   cout << "Front item of q1: " << q1.front() << endl;               //checking the first element of the object
   cout << "Front item of q2: " << q2.front() << endl << endl;       //checking the first element of the object

   cout << "Rear item of q1: " << q1.back() << endl;                  //checking the last element of the object
   cout << "Rear item of q2: " << q2.back() << endl << endl;          //checking the last element of the object

   cout << "q1: " << q1 << endl;                                      //printing the object's elemts, size and capacity
   cout << "q1 size: " << q1.size() << endl;                          //also checking to see if its empty
   cout << "q1 capacity: " << q1.capacity() << endl;
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "q2: " << q2 << endl;                                     //priting the object's elements,size and capcaity
   cout << "q2 size: " << q2.size() << endl;                         //also checking to see if its empty
   cout << "q2 capacity: " << q2.capacity() << endl;
   cout << "q2 is " << ((q2.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing pop() to empty\n\n";

   while (!q1.empty())                                              //while its not empty
      {                                                             //delete elements
      cout << q1.front() << ' ';
      q1.pop();
      }

   cout << endl;
   cout << "q1 size: " << q1.size() << endl;                        //printing elements size and capacity
   cout << "q1 capacity: " << q1.capacity() << endl;                //also checking to see if its empty
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   cout << "Testing assignment operator\n\n";

   Queue q3;

   q3 = q2;							//copying one object to another

   cout << "q2 (size " << q2.size() << "): " << q2 << endl;	//checking for their size
   cout << "q3 (size " << q3.size() << "): " << q3 << endl << endl;

   cout << "Testing clear()\n\n";

   q2.clear();							//clearing out the object

   cout << "q2 (size " << q2.size() << "): " << q2 << endl;	//checking too see if it cleared
   cout << "q3 (size " << q3.size() << "): " << q3 << endl << endl;

   cout << "Testing assignment to self and swap\n\n";

   q3 = q3;							//swapping from one object to another
   q2 = q3;
   q3.clear();							//clear object

   cout << "q2 (size " << q2.size() << "): " << q2 << endl;	//check for their size
   cout << "q3 (size " << q3.size() << "): " << q3 << endl << endl;

   cout << "Testing chained assignment\n\n";

   Queue q4;

   q4 = q3 = q2;						//chained assigment on 3 objects

   cout << "q2 (size " << q2.size() << "): " << q2 << endl;	//checking too see  if objects are equal
   cout << "q3 (size " << q3.size() << "): " << q3 << endl;
   cout << "q4 (size " << q4.size() << "): " << q4 << endl << endl;

   cout << "Testing const correctness\n\n";

   const Queue& r4 = q4; 					//printing object and its variables

   cout << "q4: " << r4 << endl;
   cout << "q4 size: " << r4.size() << endl;
   cout << "q4 capacity: " << r4.capacity() << endl;
   cout << "q4 is " << ((r4.empty()) ? "empty\n" : "not empty\n");
   cout << "Front item of q4: " << r4.front() << endl;
   cout << "Rear item of q4: " << r4.back() << endl << endl;

   q1 = r4;

   cout << "q1: " << q1 << endl;
   cout << "q1 size: " << q1.size() << endl;
   cout << "q1 is " << ((q1.empty()) ? "empty\n" : "not empty\n");
   cout << endl;

   q1.clear();

   cout << "Testing front() with empty queue\n\n";


									//checking for errors and catching them
   try
      {
	cout << q1.front() << endl;
      }
   catch (underflow_error e)
      {
      cout << "Caught "<< e.what() << endl << endl;
      }

   cout << "Testing back() with empty queue\n\n";

   try
      {
      cout << q1.back() << endl;
      }
   catch (underflow_error e)
      {
      cout << "Caught "<< e.what() << endl << endl;
      }

   cout << "Testing pop() with empty queue\n\n";

   try
     {
      q1.pop();
     }
  catch (underflow_error e)
     {
      cout << "Caught "<< e.what() << endl;
     }

   return 0;
   }
