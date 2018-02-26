/****************************************************************
   FILE:      Queue.h
   AUTHOR:    Victor P
   LOGON ID:  z1689628
   DUE DATE:  11-17-15

   PURPOSE:   This is a header file. Its a template class file
               so all code thats is usually in Queue.cpp 
               will go here as functions.
****************************************************************/

#ifndef QUICKSORT_H
   #define QUICKSORT_H

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "sorts.h"

using namespace std;
template <class T>
void quickSort(vector<T>& set, int start, int end, bool (*compare)(const T&, const T&));

template <class T>
int partition(vector<T>& set, int start, int end, bool (*compare)(const T&, const T&));

template <class T>
void quickSort(vector<T>& set, bool (*compare)(const T&, const T&))
{

  quickSort(set, 0, set.size()-1, compare);
  
}

template <class T>
void quickSort(vector<T>& set, int start, int end, bool (*compare)(const T&, const T&))
{

  int pivotPoint;
  
     if(start < end)
      {
      pivotPoint = partition(set, start, end, compare);     // Get the pivot point
      quickSort(set, start, pivotPoint - 1, compare);       // Sort first sublist
      quickSort(set, pivotPoint + 1, end, compare);         // Sort second sublist
      }

}

template <class T>
int partition(vector<T>& set, int start, int end, bool (*compare)(const T&, const T&))
{

    int pivotIndex, mid;
    T temp;
   T pivotValue;
   
   mid = (start + end) / 2;
 
    temp = set[start];
    set[start] = set[mid];
    set[mid] = temp;
    
   pivotIndex = start;
   pivotValue = set[start];
 
   for(int scan = start + 1; scan <= end; scan++)
      {
      if(compare(set[scan], pivotValue))
         {
         pivotIndex++;
         temp = set[scan];
         set[scan] = set[pivotIndex];
         set[pivotIndex] = temp;
         }
      }

    temp = set[pivotIndex];
    set[pivotIndex] = set[start];
    set[start] = temp;
    
   return pivotIndex; 
}

#endif
