/****************************************************************
   FILE:      Queue.h
   AUTHOR:    Victor P
   LOGON ID:  z1689628
   DUE DATE:  11-17-15

   PURPOSE:   This is a header file. Its a template class file
               so all code thats is usually in Queue.cpp 
               will go here as functions.
****************************************************************/

#ifndef SORTS_H
   #define SORTS_H

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert> 

using namespace std;


template <class T>
void buildList(vector<T>& set, const char* fileName)
{
  T item;
  ifstream inFile;
  
  inFile.open(fileName);
  assert(inFile);


  inFile >> item;
  
  while(!inFile.eof())
  {
    set.push_back(item);
    inFile >> item;
  }

  inFile.close();
}


template <class T>
void printList(const vector<T>& set, int itemWidth, int numPerLine)
{

  int count=0;  
  for (int i = 0; i < (int) set.size(); i++)
    {
    cout<<setw(itemWidth)<<set[i]<<' ';
    count++;
    if(count == numPerLine)
    {
      cout<<endl;
      count = 0;
    }
    
    }

   cout << endl;
}

template <class T>
bool lessThan(const T& item1, const T& item2)
{
  if(item1 < item2)
    return true;
  else
    return false;

}

template <class T>
bool greaterThan(const T& item1, const T& item2)
{

  if(item1 > item2)
    return true;
  else
    return false;
    
}

#endif