/****************************************************************
   FILE:	      Assignment8.cc
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	4/18/2016
   PURPOSE:   	Build a HastTable with an Input File
****************************************************************/
#include "assignment8.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

/****************************************************************
   FUNCTION:  get_entry

   ARGUMENTS: Constant string named line

   RETURNS:   An Entry structure 'e'

   NOTES:     This Function will get a string named line. This contains
   the information for the structure entry. It includes its key from index 2 to 4.
   We extracted and pass it over to the key field of 'e'.
   We do the same with the description.

   return the entry
****************************************************************/
Entry* get_entry (const string& line)
{
  Entry * e=new Entry();


  string key(3, ' ');
  key.at(0)=line.at(2);
  key.at(1)=line.at(3);
  key.at(2)=line.at(4);


  string description(50, ' ');
  for(int i=6; (unsigned)i<line.length();i++)
    description.at(i-6)=line.at(i);
  e->key=key;
  e->description=description;

  return e;
}

/****************************************************************
   FUNCTION:  get_key

   ARGUMENTS: Constant string named line

   RETURNS:   a string

   NOTES:     Here we pass in the the line obtain from the txt file
   It contains the key at fields 2 to 3.
   We create a new string and concatenate the string with the elements.
****************************************************************/
string get_key(const string& line)
{
  string key;
  key+=line[2];
  key+=line[3];
  key+=line[4];

  return key;
}
int main(int argc, char** argv ) {

    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }

    HT ht(11);
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) {
             Entry* e = get_entry( line );
           ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);

            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 )
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;

    }

    infile.close();
    return 0;
}
