/***********************************************************
CSCI 340 - Assignment 2 - Fall 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: Feb 8, 2016

Purpose: This program will create a vector with 10000 random integers.
It will compare elemts from one vector to another and count them too see if
both Vectors contain the element. After all the numbers are counted for a percentage out of 5000 is calculated.
************************************************************/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip> 

using namespace std; 

const int TOBE_SEARCHED = 5000;

/***************************************************************
Function: genRndNums

Use: This function will generate random numbers and push them 
into the vector. 

Parameters: A vector to push the numbers into. A vector size
to set an amount of numbers to create. A seed to create random numbers.

Returns: Returns nothing

Notes: v.push_back will put the numbers at the end of the vector. 
We use "%10000 + 1" to determine the range of numbers to pick from,
which is from 1 to 10000. 
***************************************************************/

void genRndNums( vector<int>& v, int vec_size, int seed ) {
  srand(seed);
  
  for(int i=0; i<vec_size; i++){
    
    int number = rand() % 10000 + 1;
    v.push_back(number);
  
    }
}

/***************************************************************
Function: linearSearch

Use: This function will search through the vector to see if 'x' is in it. 

Parameters: An integer to look for and a vector to search from.

Returns: The position of where 'x' is located

Notes: we create an interator 'it' and use it to store the value 
found through 'find'. With that we search for the position of the value. 
 
***************************************************************/
int linearSearch( const vector<int>& v, int x) {
  vector<int> s;
  s=v;
  
  vector<int>::iterator it;

  it = find (s.begin(), s.end(), x);
  if (it != s.end()){
      for(int i=0; i< s.size(); i++){
    if(*it == s.at(i))
      return i;
      }
  }
  else
    return -1;
}

/***************************************************************
Function: binarySearch

Use: This function will search through the vector to see if 'x' is in it in a binary search.  

Parameters: An integer to look for and a vector to search from.

Returns: The position of where 'x' is located

Notes: We get the boundary of where x is located at, if found use the first
position to look for the locations and send it back at an integer. 
 
***************************************************************/
int binarySearch( const vector<int>& v, int x) {
  
  vector<int> s;
  s=v;
  pair<vector<int>::iterator,vector<int>::iterator> bounds;
  
  bounds = equal_range(s.begin(), s.end(), x);
  
  if (bounds.first - 1  != s.end() - 0){
      for(int i=0; i< s.size(); i++){
    if(*bounds.first == s.at(i))
      return i;
      }
  }
  else
    return -1;
  
  
}
/***************************************************************
Function: search

Use: Directs the values and vector to whether we want to use binary search or linear. 

Parameters: Two vectors and a pointer to a function to do the search. 

Returns: Returns the amount of times a number was found in the vector.

Notes: get one element at a time from one vector and look for it in the other vector. 
The method to do the search is provided with the pointer *p to a function.
 
***************************************************************/
int search( const vector<int>& container, const vector<int>& searchNums, int (*p)( const vector<int>&, int) ){
  
  int count=0;
  
  for(int i=0; i < searchNums.size(); i++){
    int a = p(container, searchNums.at(i) );
    if(a != -1)
      count++;
  }
  
  return count;  
  
}

/***************************************************************
Function: sortVec

Use: Sort the vector from smallest to greatest 

Parameters: Vector to sort 

Returns: nothing

Notes: Simply input the beginning and end of the Vector into the sort function
 
***************************************************************/
void sortVec (vector<int>& v) {
  
  sort(v.begin(),v.end());
}

/***************************************************************
Function: printStat

Use: Calculate what percentage of one vector is inside the other vetor.

Parameters: The amount of times there are elements in both vectors and the initial size of the vector. 

Returns: nothing

Notes: Have the integers converted to floats for ease of division, multiply by 100 to get percentage.
Print our message stating the percentage. 
 
***************************************************************/
void printStat (int totalSucCnt, int vec_size) {

  float out =  100 * (float(totalSucCnt) / float(vec_size));
  
  cout<< "Successful searches: "<< out <<"%" << endl;
}


int main() {
    //Create two vectors and populate them with random integers
    vector<int> container, tobeSearched;
    genRndNums(container, 10000, 7);
    genRndNums(tobeSearched, TOBE_SEARCHED, 5);

    //Do a linear search and print its percent of found integers
    cout << "\nConducting linear search ..." << endl;
    int linear_search_count = search( container, tobeSearched, linearSearch );
    printStat ( linear_search_count, TOBE_SEARCHED );
  
    //produce a binary search with prints its percent of found integers
    cout << "\nConducting binary search on unsorted container ..." << endl;
    int binary_search_count = search( container, tobeSearched, binarySearch );
    printStat ( binary_search_count, TOBE_SEARCHED );

    //Sort the vector and produce a binary search with prints its percent of found integers
    sortVec( container );

    cout << "\nConducting binary search on sorted container ..." << endl;
    binary_search_count = search( container, tobeSearched, binarySearch );
    printStat ( binary_search_count, TOBE_SEARCHED );

    return 0;
}
