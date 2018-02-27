/***********************************************************
CSCI 340 - Assignment 1 - Fall 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: Feb 1, 2016

Purpose: This program will create a vector with 100 integers
The intergers are ramdomly made and then sorted in the vector
Wheh display we set a width of 10 and 10 items per line
************************************************************/ 

#include<iostream>
#include<vector>
#include<algorithm>
#include <cstdlib>
#include <iomanip> 
using namespace std; 

/***************************************************************
Function: genRndNums

Use: This function will generate random numbers and push them 
into the vector. 

Parameters: A vector to push the numbers into. A vector size
to set an amount of numbers to create. A seed to create random numbers.

Returns: Returns nothing

Notes: v.push_back will put the numbers at the end of the vector. 
We use "%1000 + 1" to determine the range of numbers to pick from,
which is from 1 to 1000. 
***************************************************************/
void genRndNums( vector<int>& v, int vec_size, int seed ) {
  srand(seed);
  
  for(int i=0; i<vec_size; i++){
    
    int number = rand() % 1000 + 1;
    v.push_back(number);
  
    }
}

/***************************************************************
Function: printVec

Use: Print the intergers inside the Vector

Parameters:The Vector to be printed and the size of the vector

Returns: Returns nothing

Notes: We set a for loop that goes through the integers and displays them.
It has a width of 10 for each number and every time ten numbers are printed it creates a new line. 
***************************************************************/
void printVec( const vector<int>& v, int vec_size ){

    for (int it = 0; it < vec_size; ++it){
    if((it%10)==0 && it>0)
    cout<<endl;
    cout <<setw(10)<<v[it];
    }
    cout<<endl;
}

int main() {
    //set the size and seed numbers
    int size = 100;
    int seed = 7;
    
    //initialize vector V
    vector<int> v;
    
    //call function to generate random  numbers
    genRndNums( v, size, seed );
    
    //call funtion to sort the vector
    sort(v.begin(), v.end());
    
    //call funtion to print out vector 'v'
    printVec(v, size);

    return 0;
}
