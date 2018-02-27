/***********************************************************
CSCI 340 - Assignment 7 - SPRING 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: April 4, 2016

Purpose: 
To create a heap from a random vector and sort the heap as well.
************************************************************/


#include<iostream>
#include<algorithm>
#include<vector>
#include <iomanip>

using namespace std;

//All the headers for the functions to be used
void build_heap ( vector < int >& v, int heap_size, bool (*compar)(int, int) );
void heapify( vector < int >& v, int heap_size, int r, bool (*compar)(int, int) );
bool less_than ( int e1, int e2 );
bool greater_than ( int e1, int e2 );
void heap_sort ( vector < int >& v, int heap_size,
bool (*compar)(int, int) );
int extract_heap ( vector < int >& v, int& heap_size, bool (*compar)(int, int) );
void print_vector ( vector < int >& v, int pos, int size );
void swap(vector <int> & v, int first, int second);


int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake    
    int heap_size = 24;
    for (int i=1; i<=heap_size; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+heap_size+1 );
    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, heap_size );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, heap_size, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, heap_size );
    heap_sort( v, heap_size, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, heap_size );
  
    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, heap_size, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, heap_size );
    heap_sort( v, heap_size, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, heap_size );
                       
    return 0;
}

/***************************************************************
Function:Build_heap

Use: to build a heap with the vector that it takes as a parameter.

Parameters:Vector, heap_size, and a pointer to a function

Returns:Nothing

Notes:This part will point to a spot in the vector to where we should
check if its heapify. 
***************************************************************/

void build_heap ( vector < int >& v, int heap_size, bool (*compar)(int, int) )
{
    for(int i=heap_size ; i >= 1; i--)
      heapify(v,heap_size,i,compar);
}

/***************************************************************
Function:heapify

Use: to make sure the vector is a heap at the provided root

Parameters: vector, heap_size, root and a pointer to a function

Returns:Nothing

Notes:This algorithm will start at the root and check if it has any children. If it does it checks which one is smaller of them two.
After that it will compare the smallest child to its parent if its violates the rule of the heap dependent of the function provided then it will swap the elements. within swapping the elements then we have to make sure the element we just swapped is in regulartion with the heap so we recall the function with the element with swap. 
***************************************************************/
void heapify( vector < int >& v, int heap_size, int i, bool (*compar)(int, int) )
{

    int left = (2*i);
    int right = (2*i)+1;

    if (right <= heap_size)
    {
      if(compar(v[left],v[right]) && compar(v[left],v[i]))
        {
          swap(v,left,i);
          heapify(v,heap_size,left,compar);
        }
      else if(compar(v[right],v[i]))
        {
          swap(v,right,i);
          heapify(v,heap_size,right,compar);
        }
    }
    else if(left <=heap_size && compar(v[left],v[i]))
          {
            swap(v,left,i);
            heapify(v,heap_size,left,compar);
          }
}

/***************************************************************
Function:Less_than

Use: check to see what numbers are bigger or smaller

Parameters: two integers

Returns:boolean

Notes:Compare two integers and check if the first one is smaller.
***************************************************************/
bool less_than ( int e1, int e2 )
{
  if(e1 < e2)
    return true;
  else
    return false;
}

/***************************************************************
Function:greater_than

Use: check to see what numbers are bigger or smaller

Parameters: two integers

Returns:boolean

Notes:Compare two integers and check if the first one is greater.
***************************************************************/
bool greater_than ( int e1, int e2 )
{
  if(e1 > e2)
    return true;
  else
    return false;
}

/***************************************************************
Function:heap sort

Use: make the heap into a vector of decending/ascending order.

Parameters: vector, heap_size,pointer to a function

Returns:nothing

Notes:request number to be added to the end of the vector. reverse the order to have the correct wanted order.
***************************************************************/
void heap_sort ( vector < int >& v, int heap_size, bool (*compar)(int, int) )
{
  for(int i=heap_size; i >0; i--){
    int a=(extract_heap(v,i,compar));
    v[i]=a;
    }
    
  reverse(v.begin()+1,v.end());
}

/***************************************************************
Function:extract_heap

Use: get the root from the heap and return it to the previous fnction.

Parameters: vector, heap_size, pointer to a function

Returns:integer

Notes:save the root to a temp number.
put the last element of the heap to the root.
heapify the new vector at the new root.
return the root that will be pushing into the vector.
***************************************************************/
int extract_heap ( vector < int >& v, int& heap_size, bool (*compar)(int, int) )
{
  int temp = v[1];
  v[1]=v[heap_size];
  heapify(v,heap_size-1,1,compar);
  return temp;
}

/***************************************************************
Function:print_vector

Use: print the vector

Parameters: vector , position to start, and size of vector

Returns:Nothing

Notes:iterate through the vector and print its elements.
The printing process will print a new line every  elements and theyre 
spaced at width 5.
***************************************************************/
void print_vector ( vector < int >& v, int pos, int size )
{
  int count=0;
  for(int i=pos; i <= size; i++)
  {
    cout<<setw(5)<<v[i];
    count++;
    if(count % 8 == 0)
      cout<<endl;
  }
}

/***************************************************************
Function:swap

Use: swap two elements in the vector

Parameters: vector, two integer positions to swap

Returns:nothing

Notes:Swap the poisitons in the vector. Create a temp value to hold the first element and then return it to the second space avalaible.
***************************************************************/


void swap(vector <int> & v, int first, int second){
  int temp=0;
  temp=v[first];
  v[first]=v[second];
  v[second]=temp;
}