#include <vector>
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
/****************************************************************
   FILE:	      Assignment9.cc     
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	5/2/2016
   PURPOSE:   	For this computer assignment, you are to write a C++ program to implement several graph
algorithms on simple graphs. These graphs are implemented with adjacency list representation
****************************************************************/
#include <iomanip>
#include <cassert>
#include "assignment9.h"
using namespace std;



/****************************************************************
   FUNCTION:  graph contructor

   ARGUMENTS: A file

   RETURNS:   Nothing

   NOTES:    Get a file and go through each line.
   The First line is the size and the second one is worthless.
   From there we start taking each line in consideration.
   We get the first element of the line and send it a vector called labels.
   We then get the rest of the info and stored the indexed number if its =1.
   This was we have a cross map. We store this in a vector list.
   
****************************************************************/

graph::graph ( const char* filename )
{
  ifstream infile(filename, ios::in);
  string line;
  getline(infile,line);
  int count= 0;   
  
  while ( !infile.eof() ) 
  {
  
    if(count == 0)
    {
      
      size =line[0] - '0';
      getline(infile,line);
 	    adj_list.resize(size);

    }
    else
    {

      
      for(int i=0; i<= size; i++)
      {
        
        if(i==0)
        {
          labels.push_back(line[i]);
        }
        else if(line[i] == '1')
        {
          adj_list[count-1].push_back(i);
        }
      }
    }
    count++;
    getline(infile,line);    
  } 
  


}

/****************************************************************
   FUNCTION:  graph desctructor

   ARGUMENTS: non

   RETURNS:   nothing

   NOTES:     clear the vector on labels and the vector list.
****************************************************************/
graph::~graph()
{
  adj_list.clear();
	labels.clear();
}

/****************************************************************
   FUNCTION:  depth first

   ARGUMENTS: integer index

   RETURNS:   nothing

   NOTES:     It first labels the indexed as already visited.
   We then Print out the label the we visited. We traverse through it map and recursevily 
   do this until we visited all the indexes.
****************************************************************/
void graph::depth_first ( int x )
{
    visited[x] = true;

     cout<< " " << labels[x] << " ";

	for (list<int>::iterator it = adj_list[x].begin(); it != adj_list[x].end(); ++it)
	{
		int w = *it-1;
		if (!visited[w])
		{
      
			display = display + "(" + labels[x] + ", " +labels[w] + ") ";
			depth_first(w);

		}
	}
}

/****************************************************************
   FUNCTION:  get_size

   ARGUMENTS: non

   RETURNS:   the size 

   NOTES:     return the size
****************************************************************/

int graph::get_size( )const
{
  return size;
}

/****************************************************************
   FUNCTION:  HT constructor

   ARGUMENTS: interger

   RETURNS:   nothing

   NOTES:    Here we check if we already traveres through an element if not then we go the 
   the function depth_first. The function returns the traverse of the map.
****************************************************************/

void graph::traverse ()
{
 cout<<"----------Traverse-----------\n\n";
	display = "";

        for(int i= 0; i < size; i++)
        {

        visited[i]= false;
        }

        for(int i = 0; i < size; i++)
        {
                if(! visited[i])
                {
                        depth_first(i);
                }
    	  }

cout<<endl;
cout<<endl;
cout<<display<<endl;
cout<<endl;

cout<<"------------end of traverse--------"<<endl<<endl;
}
/****************************************************************
   FUNCTION:  print

   ARGUMENTS: nothing

   RETURNS:   nothing

   NOTES:     Simply go through the labels and get their respective elements in 
   the adj_list. The number that belongs to the list represents a label in the vector list of labels.
****************************************************************/
void graph::print ( )const
{

cout<<"Number of vertices in the graph: "<<size<<endl;
cout<<"-----------Graph--------------"<<endl<<endl;


	for(int i = 0; i < size; i++)
	{
		cout<<labels[i]<<": ";

		for(list<int>::const_iterator it=adj_list[i].begin(); it != adj_list[i].end(); ++it)
		{
      
			cout<<labels[*it-1]<<", ";
		}
		cout<<endl;
	}


cout<<"-------------End of Graph---------------"<<endl<<endl;
}










#define ASSIGNMENT9_TEST
#ifdef 	ASSIGNMENT9_TEST

int main(int argc, char** argv) {
    if ( argc < 2 ) {
        cerr << "args: input-file-name\n";
        return 1;
    }
    
    graph g(argv[1]);

    g.print();
    
    g.traverse();

    return 0;
}

#endif
