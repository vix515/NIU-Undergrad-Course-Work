/*
VIctor Padillas
z1689628

Assignment 1
September 8, 2017

Write a program on the hopper system using C or C++.  Your executable file should be named Assign2.  It should do the following:

1. Print a message identifying the process as the original process 
   and providing its PID and its parent's PID.

2. Call fork() after printing a message saying you are about to do   
   so.  

3. If fork() fails, print an error message ("The first fork failed.") 
   and exit with a status of -1.

4. If fork() succeeds, we now have two processes:  parent and child.  

   In the child process:

   (a) Print a message identifying it as the child and providing its 
       PID and its parent's PID.  

   (b) Call fork a second time after printing a message saying you 
       are about to do so.

   (c) If fork() fails, print an error message ("The second fork 
       failed.") and exit as above.

   (d) If fork() succeeds, we now have three processes:  one parent, 
       one child and one grandchild.

       In the grandchild process:
 
       (i) Print a message identifying it as the grandchild and 
           providing its PID and its parent's PID.

       (ii) Print a message saying it is about to exit.

       (iii) Exit with a status of 0.

       In the child process (after the second fork):

       (i) Print a message identifying it as the child and 
           providing its PID and its parent's PID.

       (ii) Use wait(0) to wait for the grandchild to terminate.
         
       (iii) Print a message saying it is about to exit.

       (iv) Exit with a status of 0.

   In the parent process:

    (a) Print a message identifying it as the parent and providing 
        its PID and its parent's PID.

    (b) Call the sleep() function to sleep for 2 seconds.

    (c) Print a message saying it is about to call ps.

    (d) Use system() to execute the "ps" command.
     
    (e) Use wait(0) to wait for the child to terminate.

    (f) Print a message saying it is about to terminate.

    (g) Exit with a status of 0.

5.  The overall program should return a value of 0.

*/

#include <unistd.h>
#include <iostream>
#include <stdlib.h> 
#include  <sys/types.h>
#include <sys/wait.h>

using namespace std;
int main()
{
	//Get current PID with getpid() and parents PID with getppid()
	cerr << "I am the original process. My PID is "<< getpid() << " and my parent's PID is " << getppid() << endl;
	cerr << "Now we have the first fork"<< endl;
  
	int pid = fork(); //create a child from the original process
  
	//If an error occurs fork will throw an error and return -1
	if(pid == -1){
		cerr<< "The first fork failed" << endl;
		exit(-1);
	}
	
	//forks returns 0 with the child process 
	if(pid == 0){
		cerr<< "I am the child and my PID is "<<getpid()<< ". My parent's PID is " <<getppid() <<endl;
		
		cerr<< "Now we have the second fork()" <<endl;
		
		pid = fork(); //create a grandchild for the original process
  
		if(pid == -1){
			cerr<< "The second fork failed" << endl;
			exit(-1);
		}
		
		if(pid == 0){
			cerr<< "I am the grandchild and my PID is "<<getpid()<< ". My parent's PID is " <<getppid() <<endl;
			cerr<< "I am the grandchild, about to exit"<<endl;
			exit(0);//exit with status 0
		}
		else{
			
			cerr<< "I am the child and my PID is "<<getpid()<< ". My parent's PID is " <<getppid() <<endl;
			wait(0);//waiting on child
			cerr<< "I am the child, about to exit"<<endl;
			exit(0);
		}

	}
	
	else{
		
		cerr<< "I am the parent and my PID is "<<getpid()<< ". My parent's PID is " <<getppid() <<endl;
		sleep(2);//wait for two seconds
		system("ps");//system processes
		wait(0);
		
		cerr<< "I am the parent, about to exit." <<endl;
	}
	
	return 0;
}
