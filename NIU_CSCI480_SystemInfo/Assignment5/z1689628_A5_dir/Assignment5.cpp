/*
Victor padilla
z1689628

The program should have #defines for 5 constants:

P_NUMBER = the number of producers = 6

C_NUMBER = the number of consumers = 4

BUFFER_SIZE = the maximum size of the buffer = 12

N_P_STEPS = the number of iterations for each producer thread = 4

N_C_STEPS = the number of iterations for each consumer thread = 6

(Try running your program several times with different values. You probably want P_NUMBER * P_STEPS = C_NUMBER * C_STEPS.)

You need to create an array of C_NUMBER threads to be consumers and an array of P_NUMBER threads to be producers. These are of type pthread_t.

You need functions: Insert(), Remove(), Produce() and Consume(). Each of them has one argument, which is the ID number of a thread.

When you create a producer thread, the start_routine argument should be Produce(), and when you create a consumer thread, the start_routine argument should be Consume().

In Produce(), you need a loop to call Insert() P_STEPS times. In Consume(), you need a loop to call Remove() C_STEPS times.  When each thread reaches the end of its work, it should exit with pthread_exit().

The main program is also a thread. After creating the threads, its principal job is to wait for the other threads to terminate.  It does this using pthread_join() in a loop.  Once it is the only remaining thread, it should use sem_destroy() to get rid of the semaphores and mutex_destroy() to get rid of the mutex and then terminate itself.

Since we want to be able to follow what is happening, Insert() and Remove() should print out a message whenever they are called, stating the ID number (0 to P_NUMBER-1 or 0 to C_NUMBER-1) of the calling thread, whether it is a producer or a consumer, what it has just done, and the value of Counter, as in:

"Consumer 1 removed a widget. Total is now 2"

(As this refers to the value of Counter, it may be well do this before unlocking the mutex.)

The thread knows its ID number because we pass it to Produce() and Consume() as an argument (the argument of start_routine()), and then the ID is passed in turn to Insert() and Remove().
 
(There is a concept in LINUX of a thread ID, which we could obtain with the gettid() function, but we are not using this; we are just numbering our own threads in our own program.)

To make all this easier to follow, we will insert some delays. Each time we call Insert() or Remove(), we will then have the thread sleep for 1 second:  sleep(1). Put this in Produce() and Consume().

Most of these functions will give us an integer return value which is zero for success and nonzero for failure.  Whenever you use one of them, check the return value and if it is not 0, print an error message (using cerr or stderr) identifying what when wrong and at what point, and then exit with the value -1.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stddef.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

//Define the number of threads to create for producers and consumers
//define all other numbers that we will use through out the program
#define P_NUMBER	6
#define C_NUMBER	4
#define BUFFER_SIZE	12
#define N_P_STEPS	4
#define N_C_STEPS	6

//Initialize mutex and semaphores here so they can be accessible to all functions
pthread_mutex_t mutex;
sem_t NotFull;
sem_t NotEmpty;
int counter = 0;  //counter to keep track of amount in buffer
 
//Insert function with threadid as argument.
//Convert thread id to long so we are able to use it and print it
//lock the mutex so we dont have multiple programs accessing the buffer.
//use printf to print because 'cout' will be over written by other threads
//unlock mutex when we are done to give access to other threads
void Insert(void *threadid)
{
  long tid;
 tid = (long) threadid;
  pthread_mutex_lock(&mutex);
  counter++;
  printf("Producer #%ld inserted a widget!\t Total now is %i\n", tid, counter);
  pthread_mutex_unlock(&mutex);

}

//same as insert function, decrease counter upon execution.
void Remove(void * threadid)
{
  long tid;
 tid = (long) threadid;
  pthread_mutex_lock(&mutex);
  counter--;
  printf("Consumer #%ld removed a widget!\t Total now is %i\n", tid, counter);
  pthread_mutex_unlock(&mutex);

}

//Functions the producer thread will go to first.
//each thread will so SOME_STEPS iteration
//before inserting check the semaphores to see that we can access the buffer
//use wait and post on the sempahores to access the buffer without problems
//exit the thread
void * Produce(void * threadid)
{
  for(int i=0; i < N_P_STEPS; i++){
    sem_wait(&NotFull);
    Insert(threadid);
    sem_post(&NotEmpty);
    sleep(1);
  }
  pthread_exit(NULL);
}

//same as Produce function.
void * Consume(void * threadid)
{
  for(int i=0; i < N_C_STEPS; i++){
    sem_wait(&NotEmpty);
    Remove(threadid);
    sem_post(&NotFull);
    sleep(1);
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  //create pthread array for consumers and producers
  pthread_t consumers[C_NUMBER];
  pthread_t producers[P_NUMBER];
  //variables to number threads and its return value when created
  int rc;
  long c; 
  int rp;
  long p;

  //initialize the mutex and semaphores.
  //make the second variable in the semaphores 0 so it can shareable for all threads. 
  pthread_mutex_init(&mutex,0);
  sem_init(&NotFull,0, BUFFER_SIZE);
  sem_init(&NotEmpty,0, 0);

  //create threads for consumers
  for(c=0; c < C_NUMBER; c++)
  {
   rc = pthread_create(&consumers[c], NULL, Consume, (void *) c);
   if (rc)
    {
     printf("ERROR; return code from pthreadcreate() is %d\n", rc);
     exit(-1);
    }
  }

  //create threads for producers
  for(p=0; p < P_NUMBER; p++)
  {
   rp = pthread_create(&producers[p], NULL, Produce, (void *) p);
   if (rp)
    {
     printf("ERROR; return code from pthread_create() is %d\n", rp);
     exit(-1);
    }
  }

  //main thread waits for all others
  for(c=0; c < C_NUMBER; c++)
        pthread_join(consumers[c], NULL);

  for(p=0; p < P_NUMBER; p++)
        pthread_join(producers[p], NULL);
 
 //kill mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&NotFull);
    sem_destroy(&NotEmpty);
 /* This example omits the pthread_join() function. */
 /* Last thing that main() should do */
 pthread_exit(NULL);
}
