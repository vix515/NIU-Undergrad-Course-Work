/*****************************************************
Assignment 3
CSCI480
9/30/17

Victor Padilla
Z1689628

In this assignment, we implement a microshell in C/C++.   

we need to use several system calls under Linux including 
fork(), pipe() and dup().  This assignment's logic is more complex 
than in the previous assignments.  Please allocate sufficient time for this assignment (suggestion:  multiple days).

The name of the executable file should be "Assign3".

The shell does the following:

--- Print a prompt "480shell>" and wait for input.

--- Read the input typed after the prompt.

--- Execute the command typed in after the prompt and print a new 
    prompt.

--- The shell understands the commands "quit" and "q" as the special 
    commands to exit.

--- The shell understands a special symbol "||", by which you can 
    pipe the output of one command to next command.  To simplify, 
    this assignment only requires one pipe between two commands, such 
    as in "cat ourfile || sort".  Please note that the standard 
    Unix/Linux pipe is "|", which is different from what our 
    microshell would understand.

*****************************************************
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
using namespace std;


//This function will execute the users first command.
//It takes in a pipe the command array and a boolean to check for piping
//If a pipe exists then the boolean is true and will dup() the STDOUT into the write part of the pipe
//We close unecessary parts of the pipe and execvp() the command in the command array
//there it some error checkink in case the command doesn't execute
void first_command(int pipeA[], char * command[], bool pipeExists){

  if(pipeExists){
    dup2(pipeA[1], 1);
    close(pipeA[0]);
  }

  execvp(command[0], command);
  printf("can not execute first command. \n");
  exit(127);
}

//This function is only called in the main is a piping exists
//It takes in a pipe and a command array
//It dup() the STDIN from the read end of the pipe and closes the unsued end
//It will execute the command accorind to what was provided in the the pipe
void second_command(int pipeA[], char * command2[]){

  dup2(pipeA[0], 0);
  close(pipeA[1]);
  
  execvp(command2[0], command2);
  printf("can not execute second command. \n");
  exit(127);

}


int main(void)
{
  //this variable will take in the line of input submitted by the user
  char buf[1024];

  //PIDs for the two child processes
  pid_t pid;
  pid_t pid2;

  //these will be use to check the status of each child in the parent process
  int  status;
  int  status2;

  //initializes the pipe
  int pipeA[2];

  //out put the first line to ask user for input
  cout<< "480shel> ";

  //stay inside the loop and keep asking the user for input until the user quits the program
  while (fgets(buf,1024,stdin) != NULL){

    //initialize a boolean to check if user wants to pipe something, set to false by default until we check with user
    bool pipeExists = false;

    //initialize this arrays to NULL so anything that store in them gets cleared out.
    //these arrays will hold the commands that the user wants to carry out.

    char * command[1024] = {NULL, NULL, NULL};
    char * command2[1024] = {NULL, NULL, NULL};

    //Important to delete mark the last byte as 0 in our input
    buf[strlen(buf) -1] = 0;

    //initialize this number to zero to start save the tokens at this index 
    int index = 0;

    //a char * to hold the token saved by strtok
    char * ptr;
    ptr = strtok(buf, " ");

    //Loop through 'buf' and save tokens accordingly
    while(ptr != NULL){

      //If ptr is equal to q or quit then user want to exit program
      if(strcmp( ptr, "q" ) == 0){
        exit(0);
      }
      if(strcmp( ptr, "quit" ) == 0){
        exit(0);
      }

      //if ptr is equal to || user wants to pipe something and we change pipeExists to true
      if(strcmp( ptr, "||" ) == 0){
        pipeExists = true;
        index= 0;
        ptr = strtok(NULL, " ");
      }

      //enter here while user doesnt want to user pipes
      if(!pipeExists){
        command[index] = ptr;
        ptr = strtok(NULL, " ");
        index++;
      }

      //enter here if user want to use pipes
      if(pipeExists){
        command2[index] = ptr;
        ptr = strtok(NULL, " ");
        index++;
      }
    }

    //if pipes exists then initialize it
    if(pipeExists){
      pipe(pipeA);
    }

    //create first child
    if ((pid = fork()) == 0) {
      //pass in the pipe, commands and pipe to function to execute
      first_command(pipeA, command, pipeExists);
    }
    else if(pid < 0){
      //error with child
      cerr<<"error forking first child"<<endl;
    }

    // if pipe exists create a second process to execute the second part of the command
    if(pipeExists){

      //create second child 
      if ((pid2 = fork()) == 0) {
        second_command(pipeA, command2);
      }
      else if(pid2 < 0){
        //error with second child
        cerr<<"error forking second child"<<endl;
      }
    }

    //if the pipe was created then we close its ends
    if(pipeExists){
      close(pipeA[0]);
      close(pipeA[1]);
    }

    //wait for the first child that ALWAYS executes
    if ( (pid = waitpid(pid, &status, 0)) < 0)
      cerr<<"error waiting for first child"<<endl;

    //wait for the second child bu only if user wanted to created to use piping
    if(pipeExists){
      if ( (pid2 = waitpid(pid2, &status2, 0)) < 0)
        cerr<<"error waiting for second child"<<endl;
    }


    cerr<<"480shell> ";

  }//endwhile
  exit(0);
} 
