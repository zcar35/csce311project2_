/** @file task1.c
* Demonstrates semaphores to contol the synchronization of threads.
*
* This program starts a number of processes that are synchronized with
* semaphores to control the text output.
*
* @author Robert van Engelen
* Modified 3/1/21 with permission by CAC
**/

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#ifdef _POSIX_THREADS
# include <pthread.h>
#endif

#include <semaphore.h>

void *text(void *arg);
int counter = 0; 

int code[] = { 0,1,2,3,4,5,6 };

int main()
{
  int i;
  pthread_t tid[7];
  int sem_wait(sem_t *sem);


    for (i = 0; i < 7; i++)
    pthread_create(&tid[i], NULL, text, (void*)&code[i]);

  return 0;
}

void *text(void *arg)
{
	int n = *(int*)arg;
	if(n==0)
    {
	    sem_wait(0);
    }
	sem_wait(&mutex);
    while (count != n)
    {
        sem_wait()
    }
		// wait sema0 
	//wait sema 
	
	//while counter != n
	    // wait cond var 
  

  switch (n)
  {
    case 0:
      printf("A semaphore S is an integer-valued variable which can take only non-negative\n");
      printf("values. Exactly two operations are defined on a semaphore:\n\n");
      //post sema1
      //counter++ 
      break;

    case 1:
      printf("Signal(S): If there are processes that have been suspended on this semaphore,\n");
      printf(" wake one of them, else S := S+1.\n\n");
      //post sema2
      break;

    case 2:
      printf("Wait(S): If S>0 then S:=S-1, else suspend the execution of this process.\n");
      printf(" The process is said to be suspended on the semaphore S.\n\n");
      break;

    case 3:
      printf("The semaphore has the following properties:\n\n");
      break;

    case 4:
      printf("1. Signal(S) and Wait(S) are atomic instructions. In particular, no\n");
      printf(" instructions can be interleaved between the test that S>0 and the\n");
      printf(" decrement of S or the suspension of the calling process.\n\n");
      break;

    case 5:
      printf("2. A semaphore must be given an non-negative initial value.\n\n");
      break;

    case 6:
      printf("3. The Signal(S) operation must waken one of the suspended processes. The\n");
      printf(" definition does not specify which process will be awakened.\n\n");
      break;
  }
   //Post sema
   // broadcast cond var
  pthread_exit(0);
}

