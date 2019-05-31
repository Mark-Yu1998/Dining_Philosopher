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

  chops = (pthread_mutex_t*) malloc(numPhilosophers * sizeof(pthread_mutex_t));

  //initialize pthreads
  for (;j < numPhilosophers;j++){
    sprintf(name,"%d",j);
    mdat_mutex_init(name,&chops[j],NULL);
  }

  size = numPhilosophers;

}

void
sectionRunPhilosopher(int philosopherID, int numRounds)
{
  //local variables
  int i = 0;
  int left = philosopherID;
  int right = (philosopherID + 1) % size;

  for (;i < numRounds;i++){
    
    //Pick up chopstics, left and right
    mdat_mutex_lock(&chops[left]);
    mdat_mutex_lock(&chops[right]);

    //Eat
    eat();
    //finish eating

    mdat_mutex_unlock(&chops[left]);
    mdat_mutex_unlock(&chops[right]);

    //start thinking
    think();
  }
  
  
}
