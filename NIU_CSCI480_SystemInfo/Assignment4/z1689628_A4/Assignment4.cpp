/*
Victor Padilla
z1689628

Assigment 4

The structure of the program is that a process moves from the Entry 
queue to the Ready queue, eventually becomes Active, is moved to the 
Input queue or the Output queue or back to the Ready queue as is appropriate, and eventually terminates.  We will accumulate various statistics about each process and some global statistics about the run as a whole.  

1.  Read the input file. Create processes and store them in the Entry queue.

2.  When processing starts, we have some initializations and then a loop.

3.  We have a main loop. It starts with Timer = 0. Timer is incremented at the bottom of the loop, and the loop ends when Timer reaches MAX_TIME or there are no processes left (all queues empty, Active, IActive and OActive all = 0).

At this point, various things may happen in the loop:

If the number of processes in the cycle is less than AT_ONCE, look in the Entry queue.  A process may move from the Entry queue to the Ready queue if its arrival time has been reached.  You may initially push several processes onto the queue, but later it will normally be one at a time (after another process has terminated). 

If we do not have an Active process, we need to look for one in the Ready queue.  

If we still do not have an Active process, there is little for the CPU do on this iteration of the loop:  idle time.

If we do have an Active process, what could happen to it?

--- It could come to the end of a CPU burst.  Look in the History array; you should find an Input or Output burst.  It moves to the Input queue or Output queue.

--- It could come to the end of a CPU burst which is followed by termination 
    of the process.  Look in the History array; you should find a terminator 
    ("N" and 0).

If we do not have an IActive process, we need to look for one in the Input queue.  (It might be empty:  no IActive process for a while.)

If we have an IActive process, it may come to the end of its Input burst, in which case it is moved to the Ready queue.

If we do not have an OActive process, we need to look for one in the Output queue.  (It might be empty:  no OActive process for a while.)

If we do have an OActive process, it may come to the end of its Output burst, in which case it is moved to the Ready queue.

4.  After the main loop, print summary data about the whole run, such as these (you may think of more):

--- What was the value of the Timer at the end?

--- How many processes terminated normally?

--- What was left in each queue at the end?

--- How much time was spent doing nothing (idle time)?

This description leaves out a few details, such as initializing the variables.  You may in fact need a few more variables.  You will need a Terminate() function and perhaps more.

As the program runs, print output about major events such as when a process enters the cycle from the Entry queue or when a process terminates.  When a process terminates, print what we know about it, such as:

--- its name and priority
--- how many CPU bursts occurred
--- how many Input bursts occurred 
--- how many Output bursts occurred
--- how much time was spent in the CPU
--- how much time was spent in Input
--- how much time was spent in Output
--- how much time was spent waiting in queue (other than Entry)

Whenever the timer is a multiple of HOWOFTEN, print out the state of the system:

--- the ID number of the Active process (if there is one) 
--- the ID number of the IActive process (if there is one)
--- the ID number of the OActive process (if there is one)
--- the ID numbers of the contents of the Entry, Ready, Input and Output queues 

You will need to invent the report format for all this data.  Put some effort into it and make it easy to read.  (For the queues, try printing the list of ID numbers all on one line.)

Notice that there may be occasions when all processes are doing Input or Output, the Ready queue is empty and we have idle time for the CPU.  There may be times when the Entry queue is empty because some processes have not arrived yet.  (We could theoretically have fewer than AT_ONCE processes in the cycle at such a moment.)

*/


#include <iostream>
#include <fstream>
#include <queue>
#include <sstream> 
#include <stddef.h> 
using namespace std;

//A class that will hold the Process objects.
//It holds all the data that we will use to assess the process 
class Process {
    public:
    string name;
    int priority;
    int processID;
    int arrivalTime; //the time is can go inside the ready queue
    int arriveAt; //the time that it actually goes into the ready queue
    char historyType[255];
    int historyInt[255];
    int sub = 0;
    int cpuTimer;
    int ioTimer;
    int cpuTotal = 0;
    int iTotal = 0;
    int oTotal = 0;
    int cpuCount = 0;
    int iCount =0;
    int oCount =0;
};

int main(int argc, char *argv[])
{
  //Create 4 queues that will hold the processes
  //a deque allows us to access the processes at any indexed not just front or back
  deque<Process> entry;
  deque<Process> ready;
  deque<Process> input;
  deque<Process> output;
  
  //temp proccesses that will hold the processes that are currently been active or inputActive or outputActive
  Process active;
  Process iActive;
  Process oActive;
  
  //initialize the process id as 0, this way we know that theyre empty if its 0
  active.processID = 0;
  iActive.processID = 0;
  oActive.processID = 0;
  
  int processID = 101;  //start of the ID'ing process
  int max = 0; //amount of possible process running at once
  int idleTime = 0; //idle time for CPU
  int terminationAmount = 0; //counter for how any processes terminate properly
  
  ifstream file("file.txt");//get file

  if(!file) {
    cout << "Cannot open input file.\n";  //error checking on file
    return 1;
  }

  string line;

  while(getline(file, line)){ //pass the the information of the file line by line
    
    Process newPro;
    istringstream inLine(line);
    
    if(inLine){ //for all elements separated by a space character save it accordingly
      inLine>>newPro.name;
      inLine>>newPro.priority;
      inLine>>newPro.arrivalTime;
      newPro.processID = processID;
      processID++;
    }
    
    if(newPro.name == "STOPHERE"){//stop if we found the termination flag
      break;
    }
    
    getline(file, line);//get next line, the one that holds the bursts
    istringstream inLine2(line);
    for(int i=0; i < 20; i++){
      if(inLine2)inLine2>>newPro.historyType[i];//save character of wheter the process is active, input or output
      if(inLine2)inLine2>>newPro.historyInt[i];//save the clocks ticks for the character at indexed i
    }
    entry.push_back(newPro); // push into deque
  }
  file.close();//close file
  
  int time=0;
  
  while(time < 500){ // do the loop for 500 clock ticks

    /*
    If the CPU is not been occupied by a process (0) then we go into the ready queue and look for one.
    We check that the ready queue is not empty and if its empty then set the active process id to 0.
    Put any process from the queue in active mode. Then go through the ready queue and check if we have the 
    highest priority process active. If we dont then we change the one that we are comparing it with. 
    Once we have the highest priority Process as active then we look for it in our ready queue. Once we found
    the indexed in our ready queue we switch it with the process in the front of the ready queue and then delete
    the front element of the queue. We also do a comparison to check that if we have same priorities for two processes
    then we go to their arrival time for comparison.
    Once we made a process Active raise the counter of the CPU bursts.
    */
    if(active.processID == 0){
      if(!ready.empty()){
        active = ready.front();
        for(int i=0; i<ready.size() ; i++){
          if(ready[i].priority == active.priority){
            if(ready[i].arrivalTime <= active.arrivalTime){
              active = ready[i];
              active.cpuCount++;
            }
          }
          else if(ready[i].priority > active.priority){
            active = ready[i];
            active.cpuCount++;
          }
        }
        for(int i=0; i<ready.size(); i++){
          if(ready[i].priority == active.priority && ready[i].processID == active.processID){
            ready[i] = ready.front();
            ready.pop_front();
          }
        }
      }
      else{
        active.processID = 0;;
      }
    }
    //Same as Active but we do it for iActive
    if(iActive.processID == 0){
      if(!input.empty()){
        iActive = input.front();
        for(int i=0; i<input.size(); i++){
          if(input[i].priority == iActive.priority){
            if(input[i].arrivalTime <=  iActive.arrivalTime){
              iActive = input[i];
              iActive.iCount++;
            }
          }
          else if(input[i].priority > iActive.priority){
            iActive = input[i];
            iActive.iCount++;
          }
        }
        for(int i=0; i<input.size(); i++){
          if(input[i].priority == iActive.priority && input[i].processID == iActive.processID){
            input[i] = input.front();
            input.pop_front();
          }
        }
      }
      else{
        iActive.processID = 0;;
      }
    }
    //Same as iActive and oActive
    if(oActive.processID == 0){
      if(!output.empty()){
        oActive = output.front();
        for(int i=0; i<output.size() ; i++){
          if(output[i].priority == oActive.priority){
            if(output[i].arrivalTime <=  oActive.arrivalTime){
              oActive = output[i];
              oActive.oCount++;
            }
          }
          else if(output[i].priority > oActive.priority){
            oActive = output[i];
            oActive.oCount++;
          }
        }
        for(int i=0; i<output.size(); i++){
          if(output[i].priority == oActive.priority  && output[i].processID == oActive.processID){
            output[i] = output.front();
            output.pop_front();
          }
        }
      }
      else{
        oActive.processID = 0;;
      }
    }

    /*
    Here we check if the ready queue is empty and if it we check that we have less than 5 processes running.
    If its empty and we can add a process than we just get the one from the front of the entry queue.
    increase our max variable to record how many process we have running. WE also check that the time is the right time 
    for the process to enter.
    */
    for(int i = 0; i <10; i++){
      if(!entry.empty()){
        if(entry.front().arrivalTime <= time && max < 5){
          entry.front().arriveAt= time;
          ready.push_back(entry.front());
          cout<<"Process "<<entry.front().processID<<" moved from the Entry Queue into the Ready Queue at time "<<time<<endl<<endl;
          entry.pop_front();
          max++;
        }
      }
    }

    //for every interval of 25 clock ticks we write a report of the current status
    if(time % 25 == 0){
      cout<<"-----------------------------------------------------------------------------";
      cout<<"\nAt intervail time: "<<time<<endl;
      cout<<"\nContents in the Entry Queue:"<<endl;
      for(int i=0; i < entry.size(); i++){
        cout<<entry[i].processID<<" Priority = "<<entry[i].priority<<" arriving at time = "<<entry[i].arrivalTime<<endl;
      }
      if(entry.size() == 0){
        cout<<"empty"<<endl;
      }
      
      cout<<"Contents in the Ready Queue:"<<endl;
      for(int i=0; i < ready.size(); i++){
        cout<<ready[i].processID<<"("<<ready[i].priority<<")\t";
      }
      if(ready.size() == 0){
        cout<<"empty";
      }
      cout<<endl;
      
      cout<<"Contents in the Input Queue:"<<endl;
      for(int i=0; i < input.size(); i++){
        cout<<input[i].processID<<"("<<input[i].priority<<")\t";
      }
      if(input.size() == 0){
        cout<<"empty";
      }
      cout<<endl;
      
      cout<<"Contents in the Output Queue:"<<endl;
      for(int i=0; i < output.size(); i++){
        cout<<output[i].processID<<"("<<output[i].priority<<")\t";
      }
      if(output.size() == 0){
        cout<<"empty";
      }
      cout<<endl;


      cout<<"Active is: "<<active.processID<<endl;
      cout<<"IActive is: "<<iActive.processID<<endl;
      cout<<"OActive is: "<<oActive.processID<<endl;
      cout<<"\n-----------------------------------------------------------------------------"<<endl;
    }

    //check to see if the CPU is idle
    if(active.processID == 0){
      idleTime++;
    }

    /*
    Here we check if the ticks for the current process is over. 
    If the ticks for current process has reached zero then we check in the 
    history of character what the process wants to do next. If its an 'I' then we move it to the
    input queue, otherwise we move it to the output queue but if its neither of the two then its has come to a 
    'N' and that means terminate the process. 
    Once we terminate the process we print its information.
    we decrease the amount of processes currently running and we increase the termination counter. 
    */
    if(active.processID > 0){
      if(active.historyInt[active.sub] == 0){
        if((char)active.historyType[active.sub + 1] == 'I'){
          active.sub++;
          input.push_back(active);
          active.processID = 0;        
        }
        else if((char)active.historyType[active.sub + 1] == 'O'){
          active.sub++;
          output.push_back(active);
          active.processID = 0;
        }
        else{
          cout<<"A process has terminated"<<endl;
          cout<<"Name and ID:\t"<<active.name<<"\t"<<active.processID<<endl;
          cout<<"Priority: "<<active.priority<<endl;
          cout<<"CPU Time: "<<active.cpuTotal<<" with "<<active.cpuCount<<" CPU bursts"<<endl;
          cout<<"Input Time: "<<active.iTotal<<" with "<<active.iCount<<" Input bursts"<<endl;
          cout<<"OutPut Time: "<<active.oTotal<<" with "<<active.oCount<<" Output bursts"<<endl;
          cout<<"Arrived at: "<<active.arriveAt<<endl;
          cout<<"Time of termination: "<<time<<endl<<endl;
          active.processID = 0;
          max--;
          terminationAmount++;
        }
      }
      else{
        active.cpuTotal++;
        active.historyInt[active.sub]--;
        
      }
    }

    //similar as above
    if(iActive.processID > 0){
      if(iActive.historyInt[iActive.sub] == 0){
        if((char)iActive.historyType[iActive.sub + 1] == 'C'){
          iActive.sub++;
          ready.push_back(iActive);
          iActive.processID = 0;        
        }
        else if((char)iActive.historyType[iActive.sub + 1] == 'O'){
          iActive.sub++;
          output.push_back(iActive);
          iActive.processID = 0;
        }
        else{
          cout<<"A process has terminated"<<endl;
          cout<<"Name and ID:\t"<<iActive.name<<"\t"<<iActive.processID<<endl;
          cout<<"Priority: "<<iActive.priority<<endl;
          cout<<"CPU Time: "<<iActive.cpuTotal<<" with "<<iActive.cpuCount<<" Output bursts"<<endl;
          cout<<"Input Time: "<<iActive.iTotal<<" with "<<iActive.cpuCount<<" CPU bursts"<<endl;
          cout<<"OutPut Time: "<<iActive.oTotal<<" with "<<iActive.cpuCount<<" Input bursts"<<endl;
          cout<<"Arrived at: "<<iActive.arriveAt<<endl;
          cout<<"Time of termination: "<<time<<endl<<endl;
          iActive.processID = 0;
          max--;
          terminationAmount++;
        }
      }
      else{
        iActive.iTotal++;
        iActive.historyInt[iActive.sub]--;
        
      }
    }
    //similar as above
    if(oActive.processID > 0){
      if(oActive.historyInt[oActive.sub] == 0){
        if((char)oActive.historyType[oActive.sub + 1] == 'I'){
          oActive.sub++;
          input.push_back(oActive);
          oActive.processID = 0;        
        }
        else if((char)oActive.historyType[oActive.sub + 1] == 'C'){
          oActive.sub++;
          ready.push_back(oActive);
          oActive.processID = 0;
        }
        else{
          cout<<"A process has terminated"<<endl;
          cout<<"Name and ID:\t"<<oActive.name<<"\t"<<oActive.processID<<endl;
          cout<<"Priority: "<<oActive.priority<<endl;
          cout<<"CPU Time: "<<oActive.cpuTotal<<" with "<<oActive.cpuCount<<" CPU bursts"<<endl;
          cout<<"Input Time: "<<oActive.iTotal<<" with "<<oActive.cpuCount<<" Input bursts"<<endl;
          cout<<"OutPut Time: "<<oActive.oTotal<<" with "<<oActive.cpuCount<<" Output bursts"<<endl;
          cout<<"Arrived at: "<<oActive.arriveAt<<endl;
          cout<<"Time of termination: "<<time<<endl<<endl;
          oActive.processID = 0;
          max--;
          terminationAmount++;
        }
      }
      else{
        oActive.oTotal++;
        oActive.historyInt[oActive.sub]--;
        
      }
    }    
    time++;
    if(max == 0) break; // get out the while loop if there is no more processes. 
  }

  //Print all the data we gather from the run 
  //Also print out the queues to check what was left in them.
  cout<<"Final Value of timer is: "<<time <<endl;
  cout<<"Amount of time spent idle: "<<idleTime<<endl;
  cout<<"Amount of processes that terminated normally: "<<terminationAmount<<endl<<endl;

  cout<<"Contents in the Ready Queue:"<<endl;
      for(int i=0; i < ready.size(); i++){
        cout<<ready[i].processID<<"("<<ready[i].priority<<")\t";
      }
      if(ready.size() == 0){
        cout<<"empty";
      }
      cout<<endl;
      
      cout<<"Contents in the Input Queue:"<<endl;
      for(int i=0; i < input.size(); i++){
        cout<<input[i].processID<<"("<<input[i].priority<<")\t";
      }
      if(input.size() == 0){
        cout<<"empty";
      }
      cout<<endl;
      
      cout<<"Contents in the Output Queue:"<<endl;
      for(int i=0; i < output.size(); i++){
        cout<<output[i].processID<<"("<<output[i].priority<<")\t";
      }
      if(output.size() == 0){
        cout<<"empty";
      }
      cout<<endl;
  return 0;
}