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
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sema[7];

int main() {
    int i, j;
    pthread_t tid[7];
    pthread_mutex_t mutex;
    int ret;
    int counter;

    for (i = 0; i < 7; i++)
    {
    pthread_create(&tid[i], NULL, text, (void *) &code[i]);
}

    for (j=0;j<7;j++)
    {
        pthread_join(tid[j],NULL);
    }


  return 0;
}

void *text(void *arg)
{
    int ret;
    pthread_mutex_lock(&mutex);
   //pthread_mutex_lock();
	int n = *(int*)arg;

	if(n!=counter)
    {
	    if(n==1)
        {
            sem_wait(&sema[1]);

        }
        if (n==2)
        {
            sem_wait(&sema[2]);

        }
        if(n==3)
        {
            sem_wait(&sema[3]);


        }
        if(n==4)
        {
            sem_wait(&sema[4]);

        }
        if(n==5)
        {
            sem_wait(&sema[5]);
        }
        if(n==6)
        {
            sem_wait(&sema[6]);
        }
        if(n==7)
        {
            sem_wait(&sema[7]);

        }
    }
    if (n==counter)
    {
        counter++;
    }

  switch (n)
  {
    case 0:
      printf("A semaphore S is an integer-valued variable which can take only non-negative\n");
      printf("values. Exactly two operations are defined on a semaphore:\n\n");
      sem_post(&sema[1]);
      //counter++;
      break;

    case 1:
      printf("Signal(S): If there are processes that have been suspended on this semaphore,\n");
      printf(" wake one of them, else S := S+1.\n\n");
      sem_post(&sema[2]);
      //counter++;
      break;

    case 2:
      printf("Wait(S): If S>0 then S:=S-1, else suspend the execution of this process.\n");
      printf(" The process is said to be suspended on the semaphore S.\n\n");
      sem_post(&sema[3]);
      //counter++;
      break;

    case 3:
      printf("The semaphore has the following properties:\n\n");
      sem_post(&sema[4]);
      //counter++;
      break;

    case 4:
      printf("1. Signal(S) and Wait(S) are atomic instructions. In particular, no\n");
      printf(" instructions can be interleaved between the test that S>0 and the\n");
      printf(" decrement of S or the suspension of the calling process.\n\n");
      sem_post(&sema[5]);
      //counter++;
      break;

    case 5:
      printf("2. A semaphore must be given an non-negative initial value.\n\n");
      sem_post(&sema[6]);
      //counter++;
      break;

    case 6:
      printf("3. The Signal(S) operation must waken one of the suspended processes. The\n");
      printf(" definition does not specify which process will be awakened.\n\n");
      sem_post(&sema[7]);
      //counter++;
      break;
  }
    pthread_mutex_unlock(&mutex);

	//sem_post(sem_t *);
	pthread_exit(0);
}

