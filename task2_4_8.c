#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
	int id_num; //id
	char direct; // direction they are coming from 
	char right; // which is to the right
	int bats;
}
bat;
 //struct bat getInfo()
//{
   // struct bats b;
   // printf("Enter number of bats");
   // scanf("%d");
   // return b;
//}
//here I was trying to create a struct for the bats input.. just couldn't figure it out :(

//One mutex to get into ALL functions 
pthread_mutex_t mutex;

//Some counters: 
int total = 0; //total at intersections
int northBats = 0;
int southBats = 0;
int eastBats = 0;
int westBats = 0;
//...
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
void *goBatGo(void *arg);
void *doTheRest(void *arg);
void *arrive(void *arg);
void *cross(void *arg);
void *leave(void *arg);
void *check(void *arg);
pthread_cond_t eastQueue;
pthread_cond_t westQueue;
pthread_cond_t northQueue;
pthread_cond_t southQueue;
pthread_cond_t northFirst;
pthread_cond_t southFirst;
pthread_cond_t eastFirst;
pthread_cond_t westFirst;


int main(int argc, char **argv){
	//Let's safely assume that we will at most have 
	//100 BATs
	char directions[100];
	char  bats[100];
	pthread_mutex_t tid[100];
	//int a = getInfo(); here was supposed to go the struct
    pthread_mutex_t mutex;

    strcpy(directions, argv[1]);
	printf("Argc: %i and directions %s\n", argc, directions);
	//1) loop through input (strlen(directions)) and 
	//   create array of bat structs
	for(int i=0;i<strlen(directions);i++)
    {
	   // struct bats[i];
	   //basically here I was trying to come up with a way to populate the bats..

    }

    for (int i = 0; i <100; ++i)
    {
        pthread_create(&tid[i], NULL, goBatGo, (void *) &bats[i]);

    }



	
	//2) loop through bats now and dispatch all of
	//   the threads 
	// maybe send to a function that takes in a 
	// bat struct... 
	
	return 0;
}


void *goBatGo(void *arg){
	bat *b = (bat *) arg; 
	check(b);
	doTheRest(b);
}

void doTheRest(void *arg){//not really sure why I get an error here....
	arrive(b);
	cross(b);
	leave(b);
}

void *arrive(void *arg)
{
	bat *b = (bat *) arg; 
	pthread_mutex_lock(&mutex);
	if (b->direct == 'n')
    {
	    northBats++;
    }
	    if (northBats > 1)
        {
	        pthread_cond_wait(&northQueue, &mutex);


        }
    if (b->direct == 's')
    {
        southBats++;
    }
    if (southBats > 1)
    {
        pthread_cond_wait(&southQueue, &mutex);


    }
    if (b->direct == 'w')
    {
        westBats++;
    }
    if (westBats > 1)
    {
        pthread_cond_wait(&westQueue, &mutex);


    }
    if (b->direct == 'e')
    {
        eastBats++;
    }
    if (eastBats > 1)
    {
        pthread_cond_wait(&eastQueue, &mutex);


    }
	//...
	total++;
	pthread_mutex_unlock(&mutex);
}

void *cross(void *arg)
{
	bat *b = (bat *) arg;
    pthread_mutex_lock(&mutex);
    if (b->right == 'n' && northBats > 0)
    {
        pthread_cond_wait(&northFirst, &mutex);


    }
    if (b->direct == 'n')
    {
        northBats--;
        pthread_cond_signal(&northQueue);

    }

    if (b->right == 'e' && eastBats > 0)
    {
        pthread_cond_wait(&eastFirst, &mutex);


    }
    //...
    if (b->direct == 'w')
    {
        eastBats--;
        pthread_cond_signal(&westQueue);

    }
    if (b->right == 'w' && westBats > 0)
    {
        pthread_cond_wait(&westFirst, &mutex);


    }
    if (b->right == 's' && southBats > 0)
    {
        pthread_cond_wait(&southFirst, &mutex);


    }
    if (b->direct == 's')
    {
        northBats--;
        pthread_cond_signal(&southQueue);

    }
    //...

	//...
	total-- ;
    pthread_mutex_unlock(&mutex);

}

void *leave(void *arg)
{
	bat *b = (bat *) arg;
    pthread_mutex_lock(&mutex);

    if (b->direct == 'n')
    {
        pthread_cond_signal(&northFirst);


    }
    if (b->direct == 's')
    {
        pthread_cond_signal(&southFirst);


    }
    if (b->direct == 'e')
    {
        pthread_cond_signal(&eastFirst);


    }
    if (b->direct == 'w')
    {
        pthread_cond_signal(&westFirst);


    }
	//...
    pthread_mutex_unlock(&mutex);



}
void *check(void *arg)
{
	bat *b = (bat *) arg;
	if (total == 4)
    {
        if (b->direct == 'n')
        {
            pthread_cond_signal(&northFirst);

        }
        if (b->direct == 's')
        {
            pthread_cond_signal(&southFirst);

        }
        if (b->direct == 'e')
        {
            pthread_cond_signal(&eastFirst);

        }
        if (b->direct == 'n')
        {
            pthread_cond_signal(&eastFirst);

        }
        //return b;



    }

}

