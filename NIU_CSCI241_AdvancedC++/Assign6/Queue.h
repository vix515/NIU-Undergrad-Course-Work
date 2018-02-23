/****************************************************************
   FILE:      Queue.h
   AUTHOR:    Victor Padilla
   LOGON ID:  z1689628
   DUE DATE:  10-27-2015

   PURPOSE:   header file will contain the prototypes of the method
		          for the class Queue.
****************************************************************/
#ifndef QUEUE_H
   #define QUEUE_H

#include <fstream>
#include <stdexcept>


using namespace std;
class Queue
{
		friend ostream & operator<<(ostream & , const Queue &);	//a friend cout operator overload to output the object

        private:
                size_t queueSize;					//size of the Queue which corresponds to an unsigned int
                size_t queueCapacity;					//capacity of the Queue which corresonds to an unsigned int
                int *arr;						//an inter pointer to dynamically allocated an array of integers
		int qfront;                    //first element in list
		int qrear;                     //last element in list

	public:
		Queue();						//constructor
		~Queue();						//destructor
		Queue(const Queue &);					//copy constructor
		Queue & operator=(const Queue & );			//= operator overload method
		void clear();						//clear method
		size_t size() const;					//size getter
		size_t capacity() const;				//capacity getter
		bool empty() const;					//condition to check emptyness
		int front() const throw(underflow_error);		//method to return first element
		int back() const throw(underflow_error); 		//method to return last element
		void push(int  );					//method to set elements
		void pop() throw(underflow_error);			//method to display elements backwards
		void reserve(size_t );					//add more capacity to array
		bool operator==(const Queue & ) const;			//codition to see if objects are equal

};
#endif
