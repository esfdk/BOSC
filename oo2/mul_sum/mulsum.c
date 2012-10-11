#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct calc_struct calc;

struct calc_struct {
	double minimum_number;
	double maximum_number;
	double sumsqrt;
};

void *TaskCode(void *argument)
{
	int tid;

	// Calculation
	
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int number_of_threads = 8;
	printf("Number of threads init.");
	int input_integer = atoi(argv[1]);
	printf("Input integer calculated.");
	calc calc_result[number_of_threads];
	pthread_t threads[number_of_threads];
	double work = input_integer / number_of_threads;
		
	
	int n;
	for(n = 0; n < number_of_threads; ++n)
	{
		calc_result[n].minimum_number = floor((work * n) + 1);
		calc_result[n].maximum_number = floor(work * (n + 1));
		calc_result[n].sumsqrt = 0;	
		printf("min %d max %d", calc_result[n].minimum_number, calc_result[n].maximum_number);
	}
	
	int rc, i;

	/* create all threads */
	for (i=0; i<number_of_threads; ++i) {
		rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &calc_result[i]);
		assert(0 == rc);
	}

	/* wait for all threads to complete */
	for (i=0; i<number_of_threads; ++i) {
		rc = pthread_join(threads[i], NULL);
		assert(0 == rc);
	}

	exit(EXIT_SUCCESS);
}
