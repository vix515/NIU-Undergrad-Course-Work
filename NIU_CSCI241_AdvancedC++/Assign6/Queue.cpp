/****************************************************************
   FILE:	      Queue.cpp      
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	11-6-15
   PURPOSE:   	Method for the class Queue
****************************************************************/
#include <iostream>
#include <iomanip>
#include <cassert>
#include "Queue.h"
#include <stdexcept>

/****************************************************************

   FUNCTION:   Constructor

   ARGUMENTS:  0

   RETURNS:    nothing

   NOTES:      Creates a new object with default values.
               set the grear to be -1 when empty and increment by one
               to represent the index. 
****************************************************************/
Queue::Queue()
{
	queueSize = 0;
	queueCapacity = 0;
  	arr = new int[queueSize];
	qfront = 0;
	qrear = (queueCapacity-1);
}

/****************************************************************

   FUNCTION:   Copy Constructor

   ARGUMENTS:  0

   RETURNS:    nothing

   NOTES:      create a new element with all the same variables
               as the original 
****************************************************************/
Queue::~Queue()
{
	delete [] arr;
}


Queue::Queue(const Queue& org)
{
		queueCapacity = org.queueCapacity;
                queueSize = org.queueSize;
		qfront = org.qfront;
		qrear = org.qrear;

                arr = new int[queueCapacity ];
                assert( arr != 0 );

                for( size_t sub = 0; sub < queueCapacity; sub++ )
                arr[sub] = org.arr[sub];

}

/****************************************************************

   FUNCTION:   ostream<<

   ARGUMENTS:  ostream obj reference and a constant object reference

   RETURNS:    ostream object

   NOTES:      goes through the array and prints out the elements 
****************************************************************/

ostream & operator<<(ostream & cpy, const Queue & org)
{
	size_t current, i;
      
	for (current = org.qfront, i = 0; i < org.queueSize; ++i)
   	{
 	  	// Print queue element at subscript i
   		cpy << org.arr[current] << ' ';
   
  		 // Increment i, wrapping around to front of queue array if necessary     
  		current = (current + 1) % org.queueCapacity;
   	}
	return cpy;
}

/****************************************************************

   FUNCTION:   size
   ARGUMENTS:  0

   RETURNS:    size_t 

   NOTES:      when called returns the object's size 
****************************************************************/
size_t Queue::size() const
{
	return queueSize;
}

size_t Queue::capacity() const
{
	return queueCapacity;
}

/****************************************************************

   FUNCTION:   empty
   ARGUMENTS:  0

   RETURNS:    bool

   NOTES:      WHen called returns a boolean to see if objects is empty
****************************************************************/
bool Queue::empty() const
{
	if(queueSize == 0)
		return true;
	else
		return false;
}

/****************************************************************

   FUNCTION:   push
   ARGUMENTS:  int

   RETURNS:    0

   NOTES:      Push an element to the objects array
               if the arrays front element is not at index 0
               rearrange the array to start at 0
****************************************************************/
void Queue::push(int item)
{
	if(queueCapacity == 0)
		reserve(1);
	if(queueSize == queueCapacity)
		reserve((2*queueCapacity));
	if((qfront != 0))
	{
		int * temp = new int[queueCapacity];
		size_t current, i;

        	for (current = qfront, i = 0; i < queueSize; ++i)
        	{
                	temp[i] = arr[current];

                	current = (current + 1) % queueCapacity;
        	}
		delete [] arr;
		arr = temp;

		qfront = 0;
		qrear = queueSize - 1;
	}

	qrear = qrear + 1;
	arr[qrear] = item;
	queueSize= queueSize + 1;

}

/****************************************************************

   FUNCTION:   reserve
   ARGUMENTS:  size_t

   RETURNS:    0

   NOTES:      double up the capacity of the array
               creates more space for storage
****************************************************************/
void Queue::reserve(size_t newCapacity)
{
	queueCapacity = newCapacity;
	int * temp;
	temp = new int[queueCapacity];
	assert(temp  != 0);
	if(qfront != 0)
        {
                size_t current, i;

                for (current = qfront, i = 0; i < queueSize; ++i)
                {
                        temp[i] = arr[current];

                        current = (current + 1) % queueCapacity;
                }
                delete [] arr;
                arr = temp;

                qfront = 0;
                qrear = queueSize - 1;
        }
	for(size_t i = 0; i < queueSize; i++)
	{
		temp[i]=arr[i];
	}
		delete [] arr;
		arr = temp;
	
}
/****************************************************************

   FUNCTION:   pop
   ARGUMENTS:  0

   RETURNS:    0

   NOTES:      Deletes elements from the beginning
****************************************************************/
void Queue::pop() throw (underflow_error)
{
	if(queueSize == 0)
	throw underflow_error("queue underflow on pop()");

	qfront++;
	queueSize--;
}

/****************************************************************

   FUNCTION:   operator=
   ARGUMENTS:  const object reference

   RETURNS:    object 

   NOTES:      from one object send all the information to
               existing object. DOESNT CREATE A NEW ONE
****************************************************************/
Queue& Queue::operator=(const Queue& org)
{
	if( this != &org)
  	{
  		queueCapacity = org.queueCapacity;
  		queueSize = org.queueSize;
		qfront = org.qfront;
		qrear = org.qrear;

		delete [] arr;

  		arr = new int[queueCapacity ];
  		assert( arr != 0 );

  		for( size_t sub = 0; sub < queueCapacity; sub++ )
    		arr[sub] = org.arr[sub];
  	}

return *this;

}

/****************************************************************

   FUNCTION:   front
   ARGUMENTS:  0

   RETURNS:    int

   NOTES:      return the first element in the list 
****************************************************************/
int Queue::front() const throw (underflow_error)
{
	if(queueSize==0)
	throw underflow_error("queue underfow on front()");

	return arr[qfront];
}

/****************************************************************

   FUNCTION:   back
   ARGUMENTS:  0

   RETURNS:    int 

   NOTES:      return the last element in the list 
****************************************************************/
int Queue::back()const throw (underflow_error)
{
	if(queueSize==0)
	throw underflow_error("queue underflow on back()");
	return arr[qrear];
}

/****************************************************************

   FUNCTION:   clear
   ARGUMENTS:  0

   RETURNS:    0

   NOTES:      set all the values to the defaut state
               and empty out the array list
****************************************************************/
void Queue::clear()
{

        queueSize = 0;
        queueCapacity = 0;
        qfront = 0;
        qrear = (queueCapacity-1);

}


