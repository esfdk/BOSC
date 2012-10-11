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
	// Calculation
	calc *c = ((calc *) argument);
	double n;
	double sum = 0;
	
	for(n = c->minimum_number; n < (c->maximum_number + 1); ++n)
	{
		 sum = sum + sqrt(n);
	}
	
	c->sumsqrt = sum;
	
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	int number_of_threads = 8;
	int input_integer = atoi(argv[2]);

	calc calc_result[number_of_threads];
	pthread_t threads[number_of_threads];

	double input_double = (double) input_integer;
	double work = input_double / (double) number_of_threads;	

	int n;
	for(n = 0; n < number_of_threads; ++n)
	{
		
		double minnum = floor(work * n) + 1;
		double maxnum = floor(work * (n + 1));
		calc_result[n].minimum_number = minnum;
		calc_result[n].maximum_number = maxnum;
		calc_result[n].sumsqrt = 0;	
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

	double sumtotal = 0;
	int p;

	for(p = 0; p < number_of_threads; p++)
	{
		sumtotal = sumtotal + calc_result[p].sumsqrt;
	}
	printf("Total amount: %f \n", sumtotal);
	
	exit(EXIT_SUCCESS);
}
