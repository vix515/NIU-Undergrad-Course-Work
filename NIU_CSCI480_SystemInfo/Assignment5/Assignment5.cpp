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

  for(c=0; c < C_NUMBER; c++)
  {
   rc = pthread_create(&consumers[c], NULL, Consume, (void *) c);
   if (rc)
    {
     printf("ERROR; return code from pthreadcreate() is %d\n", rc);
     exit(-1);
    }
  }

  for(p=0; p < P_NUMBER; p++)
  {
   rp = pthread_create(&producers[p], NULL, Produce, (void *) p);
   if (rp)
    {
     printf("ERROR; return code from pthread_create() is %d\n", rp);
     exit(-1);
    }
  }

  for(c=0; c < C_NUMBER; c++)
        pthread_join(consumers[c], NULL);

  for(p=0; p < P_NUMBER; p++)
        pthread_join(producers[p], NULL);


    pthread_mutex_destroy(&mutex);
    sem_destroy(&NotFull);
    sem_destroy(&NotEmpty);
 /* This example omits the pthread_join() function. */
 /* Last thing that main() should do */
 pthread_exit(NULL);
}
