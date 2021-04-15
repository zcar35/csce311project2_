#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
	int id_num; //id
	char direct; // direction they are coming from 
	char right; // which is to the right
} bat;

//One mutex to get into ALL functions 
pthread_mutex_t mutex;

//Some counters: 
int total = 0; //total at intersections
int northBats = 0; 
//...

int main(int argc, char **argv){
	//Let's safely assume that we will at most have 
	//100 BATs
	char directions[100]; 
	strcpy(directions, argv[1]);
	printf("Argc: %i and directions %s\n", argc, directions);
	//1) loop through input (strlen(directions)) and 
	//   create array of bat structs
	
	
	//2) loop through bats now and dispatch all of
	//   the threads 
	// maybe send to a function that takes in a 
	// bat struct... 
	
	return 0; 
}

void *goBatGo(void *arg){
	bat *b = (bat *) arg; 
	//check(b);
	//doTheRest(b);
}

void doTheRest(void *arg){
	//arrive(b)
	//cross(b)
	//leave(b)
}

void *arrive(void *arg)
{
	bat *b = (bat *) arg; 
	//lock
	//if b->direct == 'n' 
	//    northBats++
	//    if northBats > 1
	//       pthread_cond_wait(&northQueue, &mutex)
	//...
	//total++
	//unlock
}

void *cross(void *arg)
{
	bat *b = (bat *) arg; 
	//lock
	//if b->right == 'n' && northBats > 0 
	      //pthread_cond_wait(&northFirst, &mutex); 
	//...
	//if b->direction == 'n'
	//   northBats--
	//   pthread_cond_signal(&northQueue);
	//...
	//total-- 
	//unlock
}

void *leave(void *arg)
{
	bat *b = (bat *) arg;
	//lock 
	//if b->direct == 'n'
	//    pthread_cond_signal(&northFirst)
	//...
	
	//unlock
}
void *check(void *arg)
{
	bat *b = (bat *) arg;
	//if total == 4
	//   if b->direct == 'n' 
	//       pthread_cond_signal(&northFirst)
}

