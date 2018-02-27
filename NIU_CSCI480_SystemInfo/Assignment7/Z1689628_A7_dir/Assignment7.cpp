/*
Victor Padilla
Z1689628
December 1, 2017

This assignment involves maintaining a File Allocation Table.

We will simulate "FAT-12" on a (very small) disk. Each block will be 512 bytes in size. With FAT-12, we have 4096 blocks, so the disk is only 2 MB in size.

Starting with an empty root directory, we will carry out a series of transactions. From time to time we will print the contents of the directory and (part) of the FAT.  

Write a program in C or C++ on the hopper system to accomplish this.  Designing your program is largely up to you.

----------------------------------------------------------------

Input File

The data in the input file is in lines.  Each line begins with 1 letter indicating the type of transaction involved. After that are more items (file name, file size) as described below.

The file ends with a line starting with '?'.  This is present as a delimiter.  

The file can be found here:

/home/turing/t90hch1/csci480/Assign7/data7.txt

----------------------------------------------------------------

What to do

The main loop of the program does the following:

Read the letter indicating which transaction is next.  After that, depending on the kind of transaction, read the rest of the data for that transaction.

Type 'C':  Copy File transaction.  The line also contains the file name and the name of the new file.

Search for the file name.  If it does not exist, we have an error.
Search for the new file name.  If it already exists, we have an error.  Create a new directory entry with the new name and the same size and then allocate space for it.

Type 'D':  Delete File transaction.  The line also contains the file name.  Search for the file name.  If it does not exist, we have an error.  Remove the directory entry for this file and deallocate the space it was using.

Type 'N':  New File transaction.  The line also contains the file name and the file size.

Search for the file name.  If it already exists, we have an error.
Create a directory entry with this name and size and then allocate space for it.

Type 'M':  Modify File transaction.  The line also contains the file name and the new file size.

Search for the file name.  If it does not exist, we have an error.
After that, the easiest way to do a Modify transaction is to use the other kinds of transactions:  New to make a new file with a temporary file name and the new size; Delete to get rid of the old file; and Rename to change the temporary file name to the name of the old file.

Type 'R':  Rename File transaction.  The line also contains the old file name and the new file name.

Search for the old file name.  If it does not exist, we have an error.  Search for the new file name.  If it already exists, we have an error.  Change the name.

Type '?":  The run ends.

----------------------------------------------------------------

Items you will probably need

You will need a table of short integers to be the FAT itself, all initialized to 0.

You will need a data structure to contain the directory entries. I suggest defining a class or struct called Entry and then having a linked list or array (or whatever) of Entry instances.  Maintain the order (chronological) of the entries.

Define a constant to represent the value 512, the number of bytes in a block.

Define a constant called HOWOFTEN with the value 6.

Define a constant to represent 12, the maximum number of entries in a directory block.

You may want to define a constant to indicate how much of the FAT to print each time.  The eventual value should be 240, but it may be convenient to use smaller values for this constant and for HOWOFTEN in developing your program.

You may want to define a function for each kind of transaction and perhaps use a switch statement.  You will also need functions to print the directory and the FAT.  You may also need an assortment of little utility functions for purposes such as:

-- searching for a file name in the directory
-- deciding how many blocks a file needs, based on its size
-- finding the first free block
-- finding the last block used by a file

----------------------------------------------------------------

Notes

You may assume that all of the transactions are valid.

The file names are no more than 20 characters long and might include a period somewhere.  They do not include blanks or other white space or other punctuation symbols.

At the beginning, the directory is empty.  At that point, it should contain only two entries named "." (the directory itself, size = 512 initially, starting block 0) and ".." (its parent directory, size 0).  We will assume a directory block can contain up to 12 entries.

When you allocate blocks to files, start with the low-numbered blocks.  We will probably never use most of the high-numbered blocks.  The last block of a file is indicated by the value -1 in the File Allocation Table.  A block not in use is indicated by the value 0 in the File Allocation Table.

Print the directory at the beginning, at the end, and after every HOWOFTEN transactions.  This should include a count of the number of files listed and the sum of their sizes.

When you print the directory, print each file's name and size and a list of the numbers of the blocks allocated to the file.

When you print the directory, also print the first 240 entries in the File Allocation Table, 12 per line.

Notice that it is legal to have a file of length 0.  For such a file, the starting block number is -1 and the directory listing should indicate "(none)" as the list of blocks.

The root directory itself should have starting block 0.  Notice that this implies FAT[0] is -1, initially.

Whenever you create or remove an entry from the directory, the directory may itself need to add a block or lose one.

Notice that we are not creating subdirectories.  We have just one directory.  The parent directory ".." does not actually exist.

Please don't print out the entire FAT, as most of it will be empty.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <iomanip>
 
using namespace std;

#define HOWOFTEN	5;

//A class to save all the files and their respective blocks
class Entry{

  public:
	int size;
	string name;
	vector<int> blocks;
};

//Initialzie the functions
void newFile(string line);
void deleteFile(string line);
void copyFile(string line);
void renameFile(string line);
void modifyFile(string line);
void print();

//Directory Vector to hold the blocks of memory in order
vector<int> directory(4096);
//Vector that holds the files of Entry object type
vector<Entry> files;

int blockSize = 512;

int main(int argc, char *argv[])
{
  //Initialize all directories to 0 to represent emptiness
  for(int i=0; i < directory.size(); i++)
    directory[i] = 0;

  //Variables to handle the data file
  ifstream file;
  file.open("data.txt");
  string line;
  
  //counters
  int j=0;
  int t = 0;
  
  print();//print the vectors
  
  //first two elements 
  newFile("N . 512");
  newFile("N .. 0");
  
  //go through file and read line by line
  while(!file.eof())
  {
    if(t%5 == 0)
      print();//print every 5 times
      
    //get line and pass it accoringly to its method
    getline(file,line);
    if(line.at(0) == 'R')
      renameFile(line);
    else if(line.at(0) == 'M')
      modifyFile(line);
    else if(line.at(0) == 'N')
      newFile(line);
    else if(line.at(0) == 'D')
      deleteFile(line);
    else if(line.at(0) == 'C')
      copyFile(line);
    else if(line.at(0) == '?')
      break;
      
    t++;
  }
  file.close();
  
  print();//print lists after all is over
    
}

//function to add new file to lists
void newFile(string line){
  
  //variables to get info from line
  char trans;
  string name;
  int size;
  
  //boolean to check if element already exists
  bool found = false;
  //object to store as file
  Entry file;

  //get info from line
  istringstream iss(line);
  iss >> trans >> name >> size;
  
  //check for file existence 
  for(int i=0; i < files.size(); i++){
    if(files.at(i).name == name)
      found == true;
  }
  
  if(found)
    cout<<"File already exists can not create new file: "<<name<<endl;
  else{
    file.name = name;
    file.size = size;
    
    //get amount of blocks to use
    int amountOfBlocks = size / blockSize;
    if(size % blockSize > 0 )
      amountOfBlocks++;
    
    //search through directory check for 0 and change it to 1 for the amount of blocks we have
    int i = 1;
    while(i <= amountOfBlocks){
      for(int j=0; j < directory.size(); j++){     
        //if the last block then set it up to be -1
        if(directory.at(j) == 0 && i == amountOfBlocks){
          directory.at(j) = -1;
          file.blocks.push_back(j);
          i++;
          break;
        }
        //else change from 0 to 1
        else if(directory.at(j) == 0){
          directory.at(j) = 1;
          file.blocks.push_back(j);
          i++;
          break;
        }
      }
    }
    //put object in list
    files.push_back(file);
  }

}

//method to delete file.
void deleteFile(string line){
  
  char trans;
  string name;

  istringstream iss(line);
  iss >> trans >> name;
  
  //go through the blocks of the file 
  //go through directory and change the value to 0 accoring to the blocks of the file
  for(int i = 0; i < files.size(); i++){
    if(name == files.at(i).name){
      for(int j = 0; j < files.at(i).blocks.size(); j++)
        directory.at(files.at(i).blocks.at(j)) = 0;
      files.erase(files.begin() + i );//erase file from list
    }
  }
}

//copy file method
void copyFile(string line){
  char trans;
  string name;
  string newName;
  bool found = false;
  bool copyFound = false;
  Entry file;
  int index;

  istringstream iss(line);
  iss >> trans >> name >> newName;
  
  //save the index of the found file
  for(int i = 0; i < files.size(); i++){
    if(files.at(i).name == name){
      file.size = files.at(i).size;
      index = i;
      found = true;
      //search the list to see if the copy already exists
      for(int j = 0; j < files.size(); j++){
        if(files.at(j).name == newName){
          copyFound = true;
        }
      }
    }
  }
  
  if(!found){
    cout<<"Cannot find file to copy: "<<name<<endl;
  }
  else{
    if(copyFound)
      cout<<"Copy with the same name as the new copy found: "<<newName<<endl;
    else{
      file.name = newName;
    
      //get the amount of blocks
      int amountOfBlocks = file.size / blockSize;
      if(file.size % blockSize > 0 )
        amountOfBlocks++;
        
        //change the empty elements from 0 to 1
        int i = 1;
        while(i <= amountOfBlocks){
          for(int j=1; j < directory.size(); j++){
            if(directory.at(j) == 0 && i == amountOfBlocks){
              directory.at(j) = -1;
              file.blocks.push_back(j);
              i++;
              break;
            }
            if(directory.at(j) == 0){
              directory.at(j) = 1;
              file.blocks.push_back(j);
              i++;
              break;
            }
          }
        }
        files.push_back(file);
    }
  }
}

//method to rename the file
void renameFile(string line){
  char trans;
  string name;
  string newName;
  bool found = false;
  bool copyFound = false;
  int index;
  
  istringstream iss(line);
  iss >> trans >> name >> newName;

  //find the file and set the boolean to true
  for(int i = 0; i < files.size(); i++){
    if(files.at(i).name == name){
      found = true;
      index = i;
    }
    //search if file atlready exists
    if(files.at(i).name == newName)
      copyFound = true;
  }
  
  if(!found)
    cout<<"No File found to be renamed, File: "<<name<<endl;
  else{
    if(copyFound)
      cout<<"File with name of copy already exists: "<<newName<<endl;
    else{
      files.at(index).name = newName;
    }
  }
}

//change size of file
void modifyFile(string line){

  char trans;
  string name;
  bool found = false;

  istringstream iss(line);
  iss >> trans >> name;
  
  //delete file 
  for(int i = 0; i < files.size(); i++){
    if(name == files.at(i).name){
      for(int j = 0; j < files.at(i).blocks.size(); j++)
        directory.at(files.at(i).blocks.at(j)) = 0;
      files.erase(files.begin() + i );
      found = true;
    }
  }
  
  //reinsert new file.
  if(found)
    newFile(line);
  else
    cout<<"File to modify changed"<<endl;
  
}

//print both lists
void print(){
  
  int j=0;
  int totalSize = 0;
  
  cout<<endl<<endl<<"Blocks occupied: "<<endl;
  for(int i =0; i < 240; i++){
    if(j % 12 == 0){
      cout<<i<<" - "<<i+11<<": "<<"\t";
    }
    cout<<directory.at(i)<<"\t";
    j++;
    if(j % 12 == 0){
      cout<<endl;
      j=0;
    }
  }
  cout<<endl;
  for(int i =0; i < files.size(); i++){
    cout<<"File Name: "<<files.at(i).name<<" \t"<<" File Size: "<<files.at(i).size<<endl;
    totalSize += files.at(i).size;
    cout<<"Blocks at"<<endl;
    for(int j=0; j < files.at(i).blocks.size(); j++){
      if(j%6 == 0 && j !=0)
        cout<<endl;
      cout<<" "<<files.at(i).blocks.at(j);
    }
    cout<<endl<<endl;
  }
  cout<<"Amount of Files: "<<files.size() - 1<<"\t"<<"Total Size: "<<totalSize<<endl<<endl;
}