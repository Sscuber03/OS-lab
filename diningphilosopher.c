// // code to simulate dining philosopher problem

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define NUM_P 5
// #define NUM_C 5

// void dine(int i)
// {
//     printf("Philosopher %d is thinking\n", i);
//     pthread_mutex_lock(&chopstick[i]);
//     pthread_mutex_lock(&chopstick[(i+1)%NUM_C]);
//     printf("Philosopher %d is eating\n", i);
//     sleep(2);
//     pthread_mutex_unlock(&chopstick[i]);
//     pthread_mutex_unlock(&chopstick[(i+1)%NUM_C]);
//     printf("Philosopher %d is done eating\n", i);
// }
// pthread_t philosopher[NUM_P];
// pthread_t chopstick[NUM_C];

// int main()
// {
//     int i, status;
//     void *msg;
//     for(int i = 1;i<=NUM_C;i++)
//     {
//         status = pthread_mutex_init(&chopstick[i], NULL);
//         if(status != 0)
//         {
//             printf("Error in mutex initialization\n");
//             exit(1);
//         }
//     }
//     for(int i = 1;i<=NUM_P;i++)
//     {
//         status = pthread_create(&philosopher[i], NULL, (void *)dine, (void *)i);
//         if(status != 0)
//         {
//             printf("Error in thread creation\n");
//             exit(1);
//         }
//     }
//     for(int i = 1;i<=NUM_P;i++)
//     {
//         status = pthread_join(philosopher[i], &msg);
//         if(status != 0)
//         {
//             printf("Error in thread joining\n");
//             exit(1);
//         }
//     }
//     return 0;
// }


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;           // counting semaphore
sem_t chopstick[5];   // binary semaphore

void * philosopher(void *);
void eat(int);

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
}

int main()
{
	int i,a[5];
	pthread_t tid[5];       // creation of threads refering to 5 philosophers
	
	sem_init(&room,0,4);   // initializations of semaphore  varring from 0 to 4.
	
	for(i=0;i<5;i++)        
		sem_init(&chopstick[i],0,1);  //initializations of binary semaphore .   
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);  // creation of philosopher and assigning it a number.
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);  // waits until a thread gets terminated
}

void * philosopher(void * num)
{
	int phil=*(int *)num;

	sem_wait(&room);                         // semaphore function to checks if resources are available.
	printf("\nPhilosopher %d has entered room",phil);
	sem_wait(&chopstick[phil]);              // semaphore function to checks if chopstick is available.
	sem_wait(&chopstick[(phil+1)%5]);

	eat(phil);
	// sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	sem_post(&chopstick[(phil+1)%5]);   // gives confirmation if semophore is released successfully 
	sem_post(&chopstick[phil]);
	sem_post(&room);
}

