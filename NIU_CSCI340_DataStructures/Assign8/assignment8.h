/****************************************************************
   FILE:	      Assignment8.h
   AUTHOR:    	Victor Padilla
   LOGON ID:  	z1689628
   DUE DATE:  	4/18/2016
   PURPOSE:   	create a structure and class for main.
****************************************************************/

#ifndef ASSIGNMENT8_H
  #define ASSIGNMENT8_H

  #include <fstream>
  #include <vector>
  #include <string>
  #include <iostream>
  #include <iomanip>
  #include <cassert>

using namespace std;

struct Entry {
    std::string key;
    std::string description;

    Entry() { key = "---"; }
};

class HT {
    private:
        std::vector<Entry>* hTable;
        int table_size;
        int item_count;
        //int hashing(const std::string&);
    public:
        HT(int size);
        ~HT();
        bool insert(const Entry&);
        int search(const std::string&);
        bool remove(const std::string&);
        void print();
        int hashVal(const std::string&);
};

/****************************************************************
   FUNCTION:  HT constructor

   ARGUMENTS: interger

   RETURNS:   nothing

   NOTES:     create a hTable with the size that was send as argument,
   also set the other variables to their respective value.
****************************************************************/

HT::HT(int s)
{
  hTable = new vector<Entry>(s);
  table_size=s;
  item_count=0;
}

/****************************************************************
   FUNCTION:  HT descontructor

   ARGUMENTS: NON

   RETURNS:   Nothing

   NOTES:     Delete the dynamically allocated memory we created
****************************************************************/
HT::~HT()
{
  delete  hTable;
}

/****************************************************************
   FUNCTION:  hashVal

   ARGUMENTS: Constant reference of a string

   RETURNS:   integer

   NOTES:     Get the key that is sent and get is ASCII value for each
   character in the key. Then add them up into one value and return them.
****************************************************************/
int HT::hashVal(const string& key)
{
  int hashVal=0;
  for(int i=0; (unsigned)i <key.length() ; i++)
      hashVal+= (int)key[i];
  return hashVal;
}

/****************************************************************
   FUNCTION:  search

   ARGUMENTS: Constant string reference

   RETURNS:   int

   NOTES:     Search for the key through the vector. If found retrn the position
   else return -1 to interpret as a 'false' was not found.
****************************************************************/
int HT::search(const string& key)
{

      for(int i=0; i < table_size; i++)
      {
        if((*hTable)[i].key == key)
          return i;
      }
          return -1;

}

/****************************************************************
   FUNCTION:  Insert

   ARGUMENTS: constant reference to an Entry

   RETURNS:   bool

   NOTES:     First check if the vector is full, if so then return false
   because we cannot add a new value. Then search to see if the value trying to be added already exist if so
   return false. If there is a space available to insert a new variable then insert into the vector. We choose its
   position through Linear Probing. First check if the position is checking if not then insert.
   If position is taken then move to the next one. This happend recursively until it finds an empty spot.
****************************************************************/

bool HT::insert(const Entry& e)
{

  if(item_count == 11)
  {
    return false;
  }
  else if(-1 == search(e.key))
  {

    int pos = hashVal(e.key) % table_size;
    if(hashVal((*hTable)[pos].key) == 45*3)
    {

      (*hTable)[pos]=e;
      item_count++;
      return true;
    }
    else
    {
      for(int i= pos +1; i < table_size; i++)
      {
        if(hashVal((*hTable)[i].key) == 45*3)
        {
          (*hTable)[i]=e;
          return true;
        }
        if(i == table_size-1)
          i=-1;
      }
    }
  }

     return false;

}

/****************************************************************
   FUNCTION:  remove

   ARGUMENTS: const string reference

   RETURNS:   bool

   NOTES:     first check to see if element exist in Vector. If so then use the position and replace
   the Key from the Vector to mimic an empty space. Else return false because the element being removed DNE.
****************************************************************/

bool HT::remove(const string& s)
{
  if(search(s) > -1)
  {
    int a=search(s);
    (*hTable)[a].key="---";
    item_count--;
    return true;
  }

  return false;
}

/****************************************************************
   FUNCTION:  print

   ARGUMENTS: nothing

   RETURNS:   Nothing

   NOTES:     Chech if there is an element at such position if so the print its position
   , key and description.
****************************************************************/

void HT::print()
{
  cout<<"----------HASH TABLE----------"<<endl;
  for(int i=0; (unsigned)i < (*hTable).size(); i++)
  if(hashVal((*hTable)[i].key) != 45*3)
  cout<<setw(3)<<i<<":"<<setw(4)<<(*hTable)[i].key<<" "<<(*hTable)[i].description<<endl;
  cout<<"------------------------------"<<'\n'<<endl;
}
#endif
