/*
Victor Padilla
z1689628

Assigment 2

Main program

1. Declare three pipe variables (which I will call Pipe A, Pipe B and 
   Pipe C).  Each is an array of two integers.

2. Call the pipe() function once for each pipe variable.  

3. If any use of pipe() fails (returning -1), print an error 
   message (such as "pipe #1 error") and exit with a status of -5.

4. Call the fork() function twice to create the three processes:
   once in the parent and then again in the child.  Do not create
   more than 3 processes.

   If fork() fails (returning -1), print an error message (such as 
   "fork #2 error") and exit with a status of -5. 

5. At this point we have three processes, parent, child and     
   grandchild.  Each of these should call a function to do the rest 
   of its work.  We can call these PWork() for the parent, CWork()  
   for the child and GWork() for the grandchild.  Before calling its 
   function, each process should close the appropriate ends of the 
   pipes it will use.  (The parent reads from Pipe C and writes to 
   Pipe A, so it should close the write end of Pipe C and the read 
   end of Pipe A, and likewise for the other two.)

   When the functions end, the processes should close the remaining
   ends of the pipes and then exit with a status of 0.  (The child
   should use wait() to wait until the grandchild terminates, and the 
   parent should do the same for the child.)
   
6. Return a value of 0.  (This is not really needed as we are using
   exit(), but it's a good habit.)

---------------------------------------------------------------------

What do the functions do?
 
1. Declare two char arrays, Buffer and Value, each of size at least 
   10.  Initialize Value to "1".  Also declare an integer M with the
   initial value 1.

   In PWork() (but not in the other two), start by writing Value to 
   the appropriate pipe.  Print a message announcing this is the 
   parent and providing the value of Value.  (This is the principal 
   difference between PWork() and the others:  it starts the 
   processing.)

2. In a loop, while M is no more than 99999999 (that is eight 9s), do 
   the following:

   (a) Read one byte at a time from the appropriate pipe and store 
       them in Value, building a string.  Stop when you find '\0'.

   (b) Make sure Value ends properly as a string with '\0'.

   (c) Convert the string Value to an integer value in M.

   (d) Compute M = 4 * M + 3.

   (e) Convert M to a string in Buffer.

   (f) Write Buffer to the appropriate pipe.  Print a message 
       identifying who is printing (parent, child or grandchild) and 
       providing the value of Value.



*/

#include <unistd.h>
#include <iostream>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;

//Header for the three main fucntions.
void pWork(int [], int[]);
void cWork(int [], int []);
void gWork(int [], int []);

using namespace std;
int main()
{

  //Create arrays of integers to hold data 
  int pipeA[2];
  int pipeB[2];
  int pipeC[2];
  
  //Create pipes and check if there was an error creating them
  if(pipe(pipeA) == -1){
  	cerr<<"Pipe A Error, exiting..."<<endl; 
  	exit(-5);
  }

  if(pipe(pipeB) == -1){
  	cerr<<"Pipe B Error, exiting..."<<endl; 
  	exit(-5);
  }

  if(pipe(pipeC) == -1){
  	cerr<<"Pipe C Error, exiting..."<<endl;  
  	exit(-5);
  }

  //Create a child off the main program
	int pid = fork(); 
  
	//If an error occurs fork will throw an error and return -1
	if(pid == -1){
		cerr<< "The first fork failed" << endl;
		exit(-5);
	}
	
	//forks returns 0 with the child process 
	if(pid == 0){

    //create a grandchild for the original process
		pid = fork(); 
  
		if(pid == -1){
			cerr<< "The second fork failed" << endl;
			exit(-5);
		}
		
    //Go inside the grandchild process
		if(pid == 0){
			
      //Close all none necessary open pipe ends and go to function. 
			close(pipeC[0]);
			close(pipeB[1]);
      gWork(pipeC, pipeB);
			close(pipeC[1]);
			close(pipeB[0]);
			
      exit(0);
		}
		else{
			
			close(pipeB[0]);
			close(pipeA[1]);
      cWork(pipeB, pipeA);
			close(pipeB[1]);
			close(pipeA[0]);

      //Wait for child to finish
		  wait(0);
			exit(0);
		}

	}
	
	else{

  	close(pipeA[0]);
  	close(pipeC[1]);
    pWork(pipeA, pipeC);
  	close(pipeA[1]);
  	close(pipeC[0]);

    wait(0);
		exit(0);

	}

	return 0;
}

//This is the function for the work of parent.
//This functions takes in two pipes, the one it reads from and the one it writes from.
//It will read from the appropriate pipe and store the value print and then converted to int
//Once its convert to int it will increase it times 4 plus 3 and send to the other process with a pipe
//it will do this until it reaches a threshold
void pWork(int pipeA[], int pipeC[]){

  char value[10] = {"1"};
  int m = 0;
  cerr<<"Parent: \t Value: "<<value<<endl;
  
  sscanf(value,"%d",&m);
  m= m*4 +3;
  string holder = to_string(m);
  const char *buffer = holder.c_str();
  write(pipeA[1],buffer,10);
  
  
  while(m <99999999){
    read(pipeC[0],value,10);
    cerr<<"Parent: \t Value: "<<value<<endl;
    sscanf(value,"%d",&m);
    m= m*4 +3;
    string holder = to_string(m);
    const char *buffer = holder.c_str();
    write(pipeA[1],buffer,10);
    
  }
}

//Similar to the pWork function
void cWork(int pipeB[], int pipeA[]){
  char value[10] = {"0"};
  int m=0;

  while(m <99999999){
    read(pipeA[0],value,10);
    cerr<<"Child:   \t Value: "<<value<<endl;

    sscanf(value,"%d",&m);
    m = m*4 +3;

    string holder = to_string(m);
    const char *buffer = holder.c_str();

    write(pipeB[1],buffer,10);
  }
	
}

//Similar to the pWork Function
void gWork(int pipeC[], int pipeB[]){
  char value[10] = {"0"};
  int m=0;

  while(m <99999999){
    read(pipeB[0],value,10);

    cerr<<"GrandChild: \t Value: "<<value<<endl;

    sscanf(value,"%d",&m);
    m = 4 *m + 3;

    string holder = to_string(m);
    const char *buffer = holder.c_str();

    write(pipeC[1],buffer,10);
    
  }
	
}
