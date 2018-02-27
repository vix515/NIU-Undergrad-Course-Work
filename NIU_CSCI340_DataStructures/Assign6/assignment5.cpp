#include "assign5.h"

//------------------------------------------------
// Do not modify this section of code
//------------------------------------------------
const int MAX_SIZE = 1000;
const int MAX_COUNT = 20;
const int WIDTH = 5;
const int ROW_SIZE = 5;
int mcount = 0;
int rcount = 0;

void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}
//--------------------------------------------
// End
//--------------------------------------------                        
                        




/***********************************************************
CSCI 340 - Assignment 5 - Fall 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: Mar 7, 2016

Purpose: This program will create a binary tree and display the first 20 elements in different orders
************************************************************/ 





//-------------------------------------------
// Do not modify this section of code
//-------------------------------------------
//#define BINTREE_MAIN
#ifdef BINTREE_MAIN

#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    vector<int> v(MAX_SIZE);    
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;
    random_shuffle( v.begin(), v.end() );
    //mcount = rcount = 0;
    //for_each( v.begin(), v.end(), display );

    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );
    

    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

#endif
//---------------------------------
// End
//--------------------------------                                             
                                              
