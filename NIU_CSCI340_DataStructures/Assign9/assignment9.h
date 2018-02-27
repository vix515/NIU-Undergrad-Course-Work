/****************************************************************
   FILE:	      Assignment9.h     
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	5/2/2016
   PURPOSE:   	For this computer assignment, you are to write a C++ program to implement several graph
algorithms on simple graphs. These graphs are implemented with adjacency list representation
****************************************************************/

#ifndef ASSIGNMENT9_H
#define ASSIGNMENT9_H
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

class graph {
    private:
        int size;
        std::vector< std::list<int> > adj_list;
        std::vector< char > labels;
        void depth_first( int );
    public:
        graph( const char* filename );
        ~graph();
        int get_size() const;
        bool visited[7];
        string display;
        void traverse( ) ;
        void print ( ) const;

};


#endif 
