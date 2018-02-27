/***********************************************************
CSCI 340 - Assignment 4 - Fall 2016

Progammer: Victor Padilla
Z-ID: z1689628
Date Due: Feb 22, 2016

Purpose: To build a Queue using two stacks 
We start by creating a queue element 
we read off the input whats we have
if its a push we push its value
if its a pop we pop the value
we then print out what size the queue and what number its in front

************************************************************/ 

#include <iostream>
#include "assign4.h"
#include <fstream>
#include <iomanip>
#include <cassert>
#include <string>


using std::cin;
using std::cout;
using namespace std;

int main() {
    Queue q;
    string op;
    int val = 0;
 
   cout << "operation -- size front end" << endl;
   while ( !cin.eof() ) {
        cin >> op;
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl; 
            return 1;
        }
        cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
    }

    while ( !q.empty() )
        q.pop();
    cout << "End -- size of Queue is: " << q.size() << endl;

    return 0;
}
