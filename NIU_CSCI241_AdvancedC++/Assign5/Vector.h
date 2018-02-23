/****************************************************************
   FILE:      Vector.h
   AUTHOR:    Victor Padilla
   LOGON ID:  z1689628
   DUE DATE:  10-27-2015

   PURPOSE:   header file will contain the prototypes of the method
		for the class Vector.
****************************************************************/
#ifndef VECTOR_H
   #define VECTOR_H

#include <fstream>
#include <stdexcept>

using namespace std;

class Vector
{
	friend ostream & operator<<(ostream &, const Vector &);	//a friend cout operator overload to output the object

  private:
    size_t vectorSize;					//size of the vector which corresponds to an unsigned int
    size_t vectorCapacity;					//capacity of the vector which corresonds to an unsigned int
    int *arr;						//an inter pointer to dynamically allocated an array of integers


	public:
		Vector();						//constructor
		~Vector();						//destructor
		Vector(const Vector &);					//copy constructor
		Vector & operator=(const Vector & );			//= operator overload method
		void clear();						//clear method
		size_t size() const;					//size getter
		size_t capacity() const;				//capacity getter
		bool empty() const;					//condition to check emptyness
		int front() const;					//method to return first element
		int back() const;					//method to return last element
		void push_back(int  );					//method to set elements
		void pop_back();					//method to display elements backwards
		void reserve(size_t );					//add more capacity to array
		int operator[](int )const;				//method to check for element at
		int & operator[](int );					//method to check for element at
		bool operator==(const Vector & ) const;			//codition to see if objects are equal
		//Vector(Vecotr&& other);
		//Vector& operator=(Vector&& rhs);
};
#endif
