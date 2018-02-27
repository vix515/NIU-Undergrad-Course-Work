/**
Victor Padilla
Z1689628
November 15, 2017

In this assignment, we are simulating memory management.  When a process is loaded into memory or a process requests a block of memory dynamically, the system must allocate memory, and when a process terminates or frees memory previously requested, the system must  deallocate memory.

For the sake of this assignment, we will assume we have a small computer with only 16 MB of memory.  We will assume that the operating system uses the first 3 MB, leaving 13 MB for applications.  Starting at that point, we will process several kinds of transactions:

--- Load a process into memory
--- Allocate a block of memory dynamically
--- Deallocate a block obtained earlier
--- Terminate a process, freeing all its memory

From time to time, we will print out the contents of the data 
structures involved.

A description of the input file is provided below.

Write a program in C++ on the hopper system to accomplish this.  Your
program (which may be in several files) should do the following:

--- Define a class or struct to represent one block of memory.  It should include the starting address (an integer), the size (an integer), the process ID of the owner (a string, might be blank) and the ID of the block (a string, might be blank), as well as one or two pointers to blocks.

--- Use #define to create a constant which I shall call HOWOFTEN.  
Give it the value 5.

--- Create two linked lists of blocks.  One list contains blocks that are presently in use, and the other contains blocks that are not presently in use.  I shall refer to these as InUse and Avail, respectively.

--- Initialize InUse to be empty.  

--- Initialize Avail to consist of one 1 MB block, two 2MB blocks and two 4 MB blocks, in that order.  The starting address for the first block should be at 3*1024*1024.  (Again, we are assuming the operating system uses the first 3 megabytes of memory.)

--- Before any transactions, print the contents of both lists.

--- Open and read the input file and carry out the transactions.

--- Every HOWOFTEN transactions, reprint the contents of both lists.

--- After all transactions, reprint the contents of both lists.

--- Be sure you close the input file.

Transactions:

Load transaction

Search the Avail list for the best-fit or first-fit block.  

If there is no sufficiently large block 
  print an error message
Else
  Create a new block of the correct size, recording the process 
  ID and the block ID
  Decrease the block found on Avail by that amount
  If the block on Avail is now of size 0
    Delete it
  End-If
  Insert the new block at the beginning of InUse
  Print a success message
End-If.

Allocate transaction

Search the Avail list for the best-fit or first-fit block.  

If there is no sufficiently large block 
  print an error message
Else
  Create a new block of the correct size, recording the process 
  ID and the Block ID  
  Decrease the block found on Avail by that amount
  If the block on Avail is now of size 0 
    Delete it
  End-If
  Insert the new block at the beginning of InUse
  Print a success message
End-If.

Deallocate transaction

Search the InUse list for the block with the correct process ID
and block ID.  (The combination of the two should be unique.)

If it is not found 
  Print an error message
Else
  Detach the block from InUse
  Insert it into Avail in order by starting address
  Traverse the Avail list combining any two consecutive blocks 
  for which the ending address of the first block is the starting 
  address of the second block, provided the combined block is no 
   more than 4 MB  
  Print a success message
End-If.

Terminate transaction

Search the InUse list as often as necessary to find and deallocate all blocks belonging to the indicated process.  

If there are none
  Print an error message  
Else
  Print a success message (there is no need to announce each and
  every block that is deallocated in a Terminate transaction)
End-If.

*/

#include <iostream>
#include <fstream>
#include <queue>
#include <sstream> 
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <iomanip>
 
using namespace std;

#define HOWOFTEN	5; //number defined to see how often we need to print the lists

//Block of memory
//Contains the start address in the list and the size of the block.
//When Memblock is in use initialize PID, and Name, change the size to the size needed
//Pointer are needed only if we dont inplement a <list>
class MemBlock{

  public:
	int startAddress;
	int size;
	int pID;
	string name;
	MemBlock * previous = NULL;
	MemBlock * next = NULL;
};

//Create memblocks lists gloably to use by all functions
list<MemBlock> available;
list<MemBlock> inUse;

//initialize functions
void deallocate(string); 
void terminate_(string);
void b_load(string);
void f_load(string);
void insertToAvailable(MemBlock);
void printLists();

//create size integers for megabytes and kilobytes, also keep the startaddress where 3mb are saved for the OS
int kb = 1024;
int mb = 1024*1024;
int startAddress = 3*mb;

int main(int argc, char *argv[])
{
    
  char arguement = argv[1][0];//get the input argument
  int count = 0;//counter to keep track of when to print the lists

  int sizes[5] ={mb, 2*mb, 2*mb, 4*mb, 4*mb};//first 5 memblocks with their respective size

  //create a memblock with the size from the above array
  //insert into list once its created
  for(int i = 0; i < 5; i++){
    MemBlock mem;
    mem.size = sizes[i];
    mem.startAddress = startAddress;
    startAddress = startAddress + sizes[i];
    available.push_back(mem);
  }

  //create iterator to go through lists
  list<MemBlock>::iterator it1= available.begin();
  list<MemBlock>::iterator it_i=inUse.begin();

  //variable to open files and save line by line
  ifstream file;
  file.open("data.txt");
  string line;
  
  cout<<"This is a memory-management simulation"<<endl<<endl;
  
  printLists();//print list before we start process
  
  //if argument from user is not b or f dont start simulation
  if(arguement == 'b' || arguement == 'f'){
  
    if(arguement == 'b')
      cout<<"Starting Simulation with Best-Fit method "<<endl<<endl;
    else
      cout<<"Starting Simulation with First-Fit method "<<endl<<endl;
          
    while(!file.eof())//while there still a line in the file
    {
      getline(file,line);//save line from file into string line and see what transaction it wants to do
      if(line.at(0) == 'L')
        if(arguement == 'b')
          b_load(line);
        else
          f_load(line);
      else if(line.at(0) == 'T')
        terminate_(line);
      else if(line.at(0) == 'A')
        if(arguement == 'b')
          b_load(line);
        else
          f_load(line);
      else if(line.at(0) == 'D')
        deallocate(line);
      else if(line.at(0) == '?')
        break;
      count++;
      if(count % 5 == 0)
        printLists();
      
    }
    file.close();
  }
  else{
    cout<<"Wrong argument for to start simulation."<<endl;
  }
  
  cout<<"Simulation Ended"<<endl<<endl;
  printLists();
  
}

//Method to deallocate a memblock from inuse
void deallocate(string line){
  char trans;
  int id;
  string name;
  istringstream iss(line);
  iss >> trans >> id >>name;//save all information from line of file into variables
  
  //iterators to go through list
  list<MemBlock>::iterator it1;
  list<MemBlock>::iterator it2;
  bool found = false;//flag to check that we found a block in the list
  
  //go through loop and find an item that has the same name and id
  //if found then move it to available list and erase it
  for(it1=inUse.begin(); it1 != inUse.end(); ++it1){
    if(it1->pID == id && it1->name == name){
      MemBlock mem;
      mem.size = it1->size;
      mem.startAddress = it1->startAddress;
      insertToAvailable(mem);
      inUse.erase(it1);
      it1--;
      found = true;
    }
  }
  
  if(!found)
    cout<<"No block with id "<<id<<" and name "<<name<<" found to deallocate"<<endl<<endl;
  else
    cout<<"Deallocated block with id "<<id<<" and name "<<name<<endl<<endl;

}

//function to deallocate a memblock but this time with a termination style
//same as deallocate function just that this one will do a deallocation for any process with the same ID
void terminate_(string line){
  char trans;
  int id;
  istringstream iss(line);
  iss >> trans >> id;
  list<MemBlock>::iterator it1;
  list<MemBlock>::iterator it2;
  bool found = false;
  for(it1=inUse.begin(); it1 != inUse.end(); ++it1){
    if(it1->pID == id){
      MemBlock mem;
      mem.size = it1->size;
      mem.startAddress = it1->startAddress;
      insertToAvailable(mem);
      inUse.erase(it1);
      it1--;      
      found = true;
    }
  }

  if(!found)
    cout<<"No block with id "<<id<<" to terminate"<<endl<<endl;
  else
    cout<<"Terminated all process with id "<<id<<endl<<endl;
}

//function to load memblock with first-fit method
//when we find a block that has the right amount of memory we use it right away
void f_load(string line){

  char trans;
  int id;
  int size;
  int startAddress;
  string name;
  bool found = false;//flag to check if we found a memblock available
  int compSize = 15*mb;
  istringstream iss(line);
  iss >> trans >> id >> size >>name;//save all variables from the file line

  list<MemBlock>::iterator it1;
  list<MemBlock>::iterator it2;

  //find a memblock that has a size big enough for the process
  //once its found flagged it and break out the loop
  for(it1=available.begin(); it1 != available.end(); ++it1){
    if((it1->size - size) >= 0){
      found = true;
      break;
    }
  }

  //if memblock is found then remove it from available list and insert used memblock in inUse list
  if(found){
    it1->size = it1->size - size;
    startAddress = it1->startAddress;
    it1->startAddress = it1->startAddress + size;
    
    MemBlock mem;
    mem.size = size;
    mem.startAddress = startAddress;
    mem.pID = id;
    mem.name = name;
    inUse.push_front(mem);
    
    cout<<"Successfully allocated a new memory block for "<<name<<" of size "<<size<<endl<<endl;
  }
  else{
  cout<<"Error: Could not find enough memory to load or allocate process."<<endl<<endl;
  }
  
}

//function to load memblock that has the best-fit 
//find a size of memory that can hold the process but doesnt leave a lot of memory space behind
void b_load(string line){
  char trans;
  int id;
  int size;
  int startAddress;
  string name;
  bool found = false;
  int compSize = 15*mb;
  istringstream iss(line);
  iss >> trans >> id >> size >>name;

  list<MemBlock>::iterator it1;
  list<MemBlock>::iterator it2;

  //go through list and find the rigth size for the process if found save it and keep checking until a better one is found (if any)
  for(it1=available.begin(); it1 != available.end(); ++it1){
    if((it1->size - size) < compSize && (it1->size - size) > 0){
      compSize = (it1->size - size);
      it2 = it1;
      found = true;
    }
  }

  //if found remove from available list and save the variables
  if(found){
    for(it1=available.begin(); it1 != available.end(); ++it1){
      if(it1->startAddress == it2->startAddress){
        it1->size = it1->size - size;
        startAddress = it1->startAddress;
        it1->startAddress = it1->startAddress + size;
      }
    }
    
    //create memblock and save it in inUse list
    MemBlock mem;
    mem.size = size;
    mem.startAddress = startAddress;
    mem.pID = id;
    mem.name = name;
    inUse.push_front(mem);
    
    cout<<"Successfully allocated a new memory block for "<<name<<" of size "<<size<<endl<<endl;
  }
  else{

  }
  
}

//once we deallocate memblock from inuse we need to store it back into available list
void insertToAvailable(MemBlock mem){
  list<MemBlock>::iterator it1;
  list<MemBlock>::iterator it2;
  
  bool found = false;//flag to check if we found a space to save it
  
  //go through list and if the startadress of the block in Avaliable is larger than the one in the block we want to insert
  //then we found where we want to stop our search and insert the block 
  for(it1=available.begin(); it1 != available.end(); it1++){
    if(it1->startAddress > mem.startAddress){
      available.insert(it1,mem);
      found = true;
    }
    
    if(found)break;
  }
  if(!found)available.push_back(mem);//if we didnt find a start adress big enough than our memblock we want to inser has the largest size so we push it to the end of the list

  //look for to consecutive memblock and merge them if their size is less than 4mb
  for(it1=available.begin(); it1 != --available.end(); it1++){
    it2 = it1;
    it2++;
    if((it1->size + it1->startAddress) == (it2->startAddress)){
      if((it1->size + it2->size) <= 4*mb){
        it1->size = it1->size + it2->size;
        available.erase(it2);
        it1--;
      }
    }
  }
}

//simply iterate through the list and print its contents
void printLists(){
  list<MemBlock>::iterator it1;
  int total = 0;
  
  cout<<"Available List"<<endl;
  cout<<setw(8)<<"Address"<<setw(8)<<"Size"<<endl;
  for(it1=available.begin(); it1 != available.end(); ++it1){
    cout<<setw(8)<<it1->startAddress<<setw(8)<<it1->size<<endl;
    total = total + it1->size;
  }
  if(total == 0)
    cout<<"Available list is empty"<<endl;
  cout<<"Total size of the list is: "<<total<<endl<<endl;
  
  total = 0;
  
  cout<<"InUse List"<<endl;
  cout<<setw(8)<<"Address"<<setw(8)<<"Size"<<endl;
  for(it1=inUse.begin(); it1 != inUse.end(); ++it1){
    cout<<setw(8)<<it1->startAddress<<setw(8)<<it1->size<<endl;
    total = total + it1->size;
  }
  if(total == 0)
    cout<<"Inuse list is empty"<<endl;
  cout<<"Total size of the list is: "<<total<<endl<<endl;
  
}






