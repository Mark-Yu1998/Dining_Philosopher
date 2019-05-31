//  sections1.c: mutual exclusion model sections

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "sections.h"
#include "mdat.h"

// TODO: Declare shared variables here

pthread_mutex_t* chops;
//num of philosophers == number of chopsticks
int size;
void
sectionInitGlobals(int numPhilosophers)
{
  // TODO: Complete this function
  //Local variables
  int i = 0;
  int j = 0;
  const int LENGTH = 6;
  //A name up to 6 characters
  char name[LENGTH];

  //make sure no currupted bytes
  for (;i < LENGTH;i++){
    name[i] = '\0';
  }
  //Initialize a heap allocated array
  chops = (pthread_mutex_t*) malloc(numPhilosophers * sizeof(pthread_mutex_t));

  //initialize pthreads
  for (;j < numPhilosophers;j++){
    sprintf(name,"%d",j);
    mdat_mutex_init(name,&chops[j],NULL);
  }

  //Make the number of philosopher global
  size = numPhilosophers;

}

//Resource Hierarchy
void
sectionRunPhilosopher(int philosopherID, int numRounds)
{
  //local variables
  int i = 0;
  int temp;
  int first = philosopherID ;
  int second = (philosopherID + 1) % size ;

  //check which is smaller
  if (first > second){
      temp = first;
      first = second;
      second = temp;
  }

  for (;i < numRounds;i++){
    
    //Pick up chopstics, the one with smaller index first, higher priority
    mdat_mutex_lock(&chops[first]);
    mdat_mutex_lock(&chops[second]);

    //Eat
    eat();

    //finish eating
    mdat_mutex_unlock(&chops[first]);
    mdat_mutex_unlock(&chops[second]);

    //start thinking
    think();
  }
  
  
}
