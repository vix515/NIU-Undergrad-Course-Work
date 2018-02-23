/****************************************************************
   FILE:	Vector.cpp
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	10-27-15
   PURPOSE:   	Method for the class Vector
****************************************************************/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include "Vector.h"


using namespace std;

/****************************************************************

   FUNCTION:   Constructor Vector

   ARGUMENTS:  No arguments

   RETURNS:    no return

   NOTES:      This is a Vector constructor. It takes no parameters.
		it defines the variables of the object to be 0 (empty)
		creates an empty array aswell.
****************************************************************/
Vector::Vector()
{
	vectorSize = 0;
	vectorCapacity = 0;
  	arr = new int[vectorSize];

}

/****************************************************************

   FUNCTION:  destructor

   ARGUMENTS: no arguments

   RETURNS:   no return

   NOTES:     deletes any dynamic memory create form vector array.
****************************************************************/
Vector::~Vector()
{
	delete [] arr;
}

/****************************************************************

   FUNCTION:  Vector

   ARGUMENTS: const reference to an object

   RETURNS:   no returns

   NOTES:    This is a copy contuctor. It will take as an argument
		an object and copy it as a new one. It keep the same
		vector capacity and vector size. it Passes all the
		elements as well. It creates a new array and then
		makes sure that is not empty. With a forloop it
		will copy one element at a time.
****************************************************************/
Vector::Vector(const Vector& org)
{
		            vectorCapacity = org.vectorCapacity;
                vectorSize = org.vectorSize;

                arr = new int[vectorCapacity ];
                assert( arr != 0 );

                for( int i = 0; i < vectorCapacity; i++ )
                arr[i] = org.arr[i];

}

/****************************************************************

   FUNCTION:  operator overload of <<

   ARGUMENTS: ostream const and a const object

   RETURNS:   returns a const ostream object

   NOTES:      This function takes in two parameters. A ostreams
		reference and a const Vector object. The arguments
		are label cpy for copy and org for original.
		It will use a for loop to go through the object's
		elements and print them out one by one.
****************************************************************/
ostream & operator<<(ostream & cpy, const Vector & org)
{
	size_t current, sub;

	for( sub = 0; sub < org.size(); sub++ )
	{
		cpy << org.arr[sub] << " ";
	}
	return cpy;
}


/****************************************************************

   FUNCTION:	size

   ARGUMENTS: 	no arguments

   RETURNS:   	a size_t variable

   NOTES:      this method is called to get the size of the object.
		since  its an unsigned integer we return size_t.
****************************************************************/
size_t Vector::size() const
{
	return vectorSize;
}
/****************************************************************

   FUNCTION:  	capacity

   ARGUMENTS: 	no arguments

   RETURNS:	a size_t variable

   NOTES:      	this method is called to get the capacity of the object
		since its an unsigned integer we return size_t.
****************************************************************/
size_t Vector::capacity() const
{
	return vectorCapacity;
}

/****************************************************************

   FUNCTION:  empty

   ARGUMENTS: 	no arguments

   RETURNS:   	a boolean

   NOTES:      	this is a simle method. if the size of the object
		is 0 then is empty, oherwise is not empty and
		reutrns false.
****************************************************************/
bool Vector::empty() const
{
	if(vectorSize == 0)
		return true;
	else
		return false;
}

/****************************************************************

   FUNCTION:  	push_back

   ARGUMENTS:	an integer

   RETURNS:   	no return

   NOTES:      this method will set an integer at the next available location.
		is there is no available location is will call the reserve method.
		this is for it to create more space and that way the item can be
		added to the array. if the vector capacity is 0 then it adds 1 space.
		if the size = capacity then we double the capacity.
****************************************************************/
void Vector::push_back(int item)
{
	if(vectorCapacity == 0)
		reserve(1);
	if(vectorSize == vectorCapacity)
		reserve((2*vectorCapacity));

	arr[vectorSize] = item;
	vectorSize++;
}

/****************************************************************

   FUNCTION:  	reserve

   ARGUMENTS: 	size_t newCapacity

   RETURNS:   	no return

   NOTES:      this method is a bit complex. We start by changing the
		objects capacity with the argument we send. then
		we create a temp array with the new capacity.
		we fill the temp array with the current array's elements
		inside a forloop. once our temp array has all of our original
		elements then we empty out the old array. After its empty
		we bring its elements back and put a new capacity in it.
****************************************************************/
void Vector::reserve(size_t newCapacity)
{
	vectorCapacity = newCapacity;
	int * temp;
	temp = new int[vectorCapacity];
	assert(temp  != 0);
	for(int i = 0; i < vectorSize; i++)
	{
		temp[i]=arr[i];
	}
	delete [] arr;
	arr = temp;

}

/****************************************************************

   FUNCTION: 	pop_back

   ARGUMENTS: 	no arguments

   RETURNS:   	no return

   NOTES:	this  simple method just shrinks the object's size by one.
****************************************************************/
void Vector::pop_back()
{
	vectorSize--;
}

/****************************************************************

   FUNCTION:  	operator=

   ARGUMENTS: 	const vector reference

   RETURNS:   	vector

   NOTES:      This is a complex method.
		we first check for self assigment.
		we then put the orginals and copy's capcaity and size
		equal to eachother. We delete memory and then create new memory,
		we make sure its nor empty and start the copying process. With a for loop
		going through each and one of the elements coying one to another.
		and we return the object.
****************************************************************/
Vector& Vector::operator=(const Vector& org)
{
	if( this != &org)
  	{
  		vectorCapacity = org.vectorCapacity;
  		vectorSize = org.vectorSize;

		delete [] arr;

  		arr = new int[vectorCapacity ];
  		assert( arr != 0 );

  		for( int sub = 0; sub < vectorCapacity; sub++ )
    		arr[sub] = org.arr[sub];
  	}

return *this;

}

/****************************************************************

   FUNCTION:  	front

   ARGUMENTS: 	no arguments

   RETURNS:   	an int (an element)

   NOTES:      	simple method. when called returns the element at position 0
		( the first, front, element)
****************************************************************/
int Vector::front()const
{
	return arr[0];
}

/****************************************************************

   FUNCTION:  	back

   ARGUMENTS: 	no args

   RETURNS:   	int (an element)

   NOTES:      	simple method, when called returns the last element
		its position it at the size of the array minus one
****************************************************************/
int Vector::back()const
{
	return arr[(vectorSize - 1)];
}

/****************************************************************

   FUNCTION:  clear

   ARGUMENTS: no args

   RETURNS:   no return

   NOTES:      sets the objects size to 0
****************************************************************/
void Vector::clear()
{
	vectorSize=0;
}

/****************************************************************

   FUNCTION: 	operator[]

   ARGUMENTS: 	an int

   RETURNS:   	an int

   NOTES:      returns the element at the position being requested
		( at sub)
****************************************************************/
int Vector::operator[](int sub)const
{
	return arr[sub];
}

/****************************************************************

   FUNCTION:  	operator[]

   ARGUMENTS: 	int

   RETURNS:   	a reference to an int

   NOTES:      return a reference to the elements at position being requested
****************************************************************/
int& Vector::operator[](int sub)
{
	return arr[sub];
}

/****************************************************************

   FUNCTION:  	operator==

   ARGUMENTS: 	a const object reference

   RETURNS:   	a boolean

   NOTES:      	this method will compare to see if two object are equal.
		The very first comparison it does is too see if their
		size is equal. this is becuase if one array has an extra
		or a less element than theyre definetly not equal.

		if the sizes are equal it will go into a foor loop and
		compare the elements one by one. if after the loop is over
		and there is no false stament then we can assume its true
		and return true.
****************************************************************/
bool Vector::operator==(const Vector & org)const
{
	if(vectorSize != org.vectorSize)
	{
		return false;
	}

	for(int i = 0; i < vectorSize; i++)
	{
		if(arr[i] != org.arr[i])
	 	{
			return false;
		}
	}

	return true;
}

//Vector::Vector(Vector&& other)/
//{

//}
