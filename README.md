# Dining_Philosopher

## Introduction
- [Dining Philosopher problem ](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

- In the program, I used chopsticks instead of forks. (People rarely use two forks to eat pasta)
- The program is consists of two sections
  
  1. Section 1: Creating the dining philosopher program, in which two philosophers are trying to pick up the same chopsticks
  2. Section 2: Solving the problem using resource hierarchy to prevent different philosophers pick up the same chopsticks, and make sure, some are eating, and some are thinking.

----
## Resources
- [checker.cpp](https://github.com/Mark-Yu1998/Dining_Philosopher/blob/master/checker.cpp), [checker.h](https://github.com/Mark-Yu1998/Dining_Philosopher/blob/master/checker.h): Mutual exclusion checker
- [run-mdat.py](https://github.com/Mark-Yu1998/Dining_Philosopher/blob/master/run-mdat.py): Program tester
- [think_eat.c](https://github.com/Mark-Yu1998/Dining_Philosopher/blob/master/think_eat.c): Simulate thinking and eathing by the philosophers

----
## MDAT
* MDAT will also detect other problematic situations. Including: 
  
  -  Two different philosophers who require the same chopstick are eating at the same time (implying that they are both holding the same chopstick at the same time)

  - A philosopher is starting to eat when they are already eating or the last thing they did was eating. (They should instead alternate between eating and thinking.)

  - A philosopher is starting to think without having first eaten. (This may happen if they think twice in a row, or if the first thing they do is thinking, before they eat.) Remember, never think on an empty stomach!)
  
  - A philosopher eats more times than the specified number of rounds says they should.

  - A philosopher eats fewer times (by the end of their thread) than the specified number of rounds says they should.

----
## MDAT

| pthreads function name | MDAT function name |
| ---------------------- | ------------------ |
| pthread_mutex_init     | mdat_mutex_init    |
| pthread_mutex_lock     | mdat_mutex_lock    |
| pthread_mutex_unlock   | mdat_mutex_unlock  |
| sem_init               | mdat_sem_init      |
| sem_wait               | mdat_sem_wait      |
| sem_post               | mdat_sem_post      |


#### Functions

- `void mdat_mutex_init(const char *name, pthread_mutex_t *lock pthread_mutexattr_t *attr);`
- `void mdat_mutex_lock(pthread_mutex_t *lp);`
- `void mdat_mutex_unlock(pthread_mutex_t *lp);`
- `void mdat_sem_init(const char *name, sem_t *sem, int pshared, int value);` 
- `void mdat_sem_wait(sem_t *sp);`
- `void mdat_sem_post(sem_t *sp);`

The argument lists for the MDAT functions are identical to corresponding pthreads function except for mdat_mutex_init and mdat_sem_init. These functions have an additional name argument that serves as the name of that entity. That name is subsequently used in the debugging trace in MDAT (more on that later).

---
## How to use MDAT

- MDAT takes over the scheduling responsibilities from the OS by making sure that only one thread is active at a time. During the compilation process, MDAT will instrument the files sectionsA.c and sectionsB.c to add calls to invoke the scheduler (called mdat_invoke_scheduler) after each statement in the program. Furthermore, complex statements are split into two or more basic statements adding a call to mdat_invoke_scheduler after each one. Unless you are using the interactive mode, the scheduler selects which thread to run next randomly. In addition, all other thread selection choices are made randomly. The act of randomly scheduling plus the myriad of scheduler invocations causing many context switches more aggressively tests the program than a normal pthread program.
  
- MDAT automatically checks for deadlock and mutual exclusion violations while the program runs. The mutual exclusion checker will check for the properties of the problem. The checker for mdat1 will be used to check the properties for part a and the checker for mdat2 will check the properties for part b. When an error occurs, the program will stop execution.

- To facilitate testing of many schedules (important in multithreaded testing), a script is provided called run-mdat.py which will run your implementation a user-specified number of times invoking the checker after each run. If a run fails (either to deadlock or due to checker error), the script will stop. The trace is stored in trace.mdat. The trace can be opened in Emacs or using the MDAT trace analyzer (described later in this guide) to help debug the problem.
The command line for run-mdat.py is as follows:
`./run-mdat.py -R <runs> -t <threads> -r <rounds> -m <mode (1 or 2)> [-c]`

- These four command line switches are required:
  - The –R switch is used to specify the number of runs – the number of times to run your program.
  - The –t and –r switches are used to specify the number of threads and number of rounds. These
    parameters are identical to the –t and –r switches for mdat1 and mdat2.
  - The –m switch is used to run either part 1 or 2. Specifying ‘1’ will direct the script to run mdat1 and to use ‘1’ when running the checker. Similarly, specifying ‘2’ will direct the script to run mdat2 and to use mode ‘2’ when running the checker.
  
**Note**: If you get a “permission denied” error with run-mdat.py, execute the following in the directory where run-mdat.py resides: chmod +x run-mdat.py

By default, run-mdat.py will stop anytime deadlock or a mutual exclusion error is detected. There is an optional –c flag that will direct run-mdat.py to continue past any errors.
Here is a good command line to start testing:

`./run-mdat.py –R 10 –t 6 –r 5 –m 1`

---
## Compiling
- Linux only, a `Makefile` is provided
- In some cases, if permision is denied use `chmod +x <filename>`

## Running the program

- If compiled successfully, two executables mdat1 and mdat2 will be created for parts a and b respectively. 
  
- The execution of both executables are the same. There are five command line flags, two are required and three are optional:

    - Required flags: 
      - -t `<num-threads>` (or --threads) Number of threads
      - -r `<num-rounds>` (or --rounds)  Number of rounds
    - Optional flags: 
      - -i (or --interactive) Run in interactive mode
      - -o `<filename>` - (or --output) Create output trace in specified file
      - -s `<number>` (or --seed) Sets the random number generator seed

#### Notes: 
- The required flags specify the number of threads and the number of rounds. Each thread is
 automatically assigned a type (based on the assignment in class, the different types are split evenly among the threads).

- Use the “-o” flag to create a debugging trace.
  
- By default, the scheduler will randomly select threads and is seeded by the current time. The seed is printed out at the beginning of each run. To rerun a program with a specified seed and obtain the exact same schedule, then use the “-s” option. Note: The schedule will only be the same for a particular executable with the same number of threads and rounds. If you recompile your program and/or use a different number of threads or rounds, the schedule will likely be different.
  
- Use the “-i” flag to run MDAT in interactive mode where the user gets to choose which thread runs
 next.

#### Example: 

**Runs mdat1 with 16 threads for 10 rounds. The debugging trace is placed in the file trace.mdat.**
`./mdat1 –t 16 –r 10 –o trace.mdat`

