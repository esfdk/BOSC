#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct calc_struct calc;

struct calc_struct {
	float minimum_number;
	float maximum_number;
	float sumsqrt;
};

void *TaskCode(void *argument)
{
	// Calculation
	calc c = *((calc *) argument)
	float n;
	float sum = 0;
	
	for(n = c->minimum_number; n < c->maximum_number; ++n)
	{
		 sum = sum + sqrt(n);
	}
	
	printf("%f \n", sum);
	c->sumsqrt = sum;
	
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int number_of_threads = 8;
	int input_integer = atoi(argv[2]);

	calc calc_result[number_of_threads];
	pthread_t threads[number_of_threads];

	float input_float = (float) input_integer;
	float work = input_float / (float) number_of_threads;	

	int n;
	for(n = 0; n < number_of_threads; ++n)
	{
		
		float minnum = floor(work * n) + 1;
		float maxnum = floor(work * (n + 1));
		calc_result[n].minimum_number = minnum;
		calc_result[n].maximum_number = maxnum;
		calc_result[n].sumsqrt = 0;	
		printf("min %f max %f \n", calc_result[n].minimum_number, calc_result[n].maximum_number);
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
