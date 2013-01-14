#include <stdio.h>
#include <pthread.h>

pthread_mutex_t counter_lock;
int counter;

void *counterIncrease(void *argument);

int main(int argc, char *argv[]){
	// Init counter
	counter = 0;
	// Init mutex
	pthread_mutex_init(&counter_lock, NULL);
	pthread_t threadA;
	pthread_t threadB;
	
	// Create threads
	pthread_create(&threadA, NULL, &counterIncrease, (void*) 1);
	pthread_create(&threadB, NULL, &counterIncrease, (void*) 2);

	// Join threads
	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);

	return 0;
}

void *counterIncrease(void *argument){
	while(counter < 10){

		pthread_mutex_lock(&counter_lock);
		counter++;
		printf("pid: %d, counter: %d \n", (int *) argument, counter);
		pthread_mutex_unlock(&counter_lock);

		usleep(100);
	}
	pthread_exit(0);
}
