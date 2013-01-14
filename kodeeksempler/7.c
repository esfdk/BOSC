#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	// Allocate array of two ints
	int *iarr = malloc(sizeof(int)*2);
	
	// Set initial values of array
	iarr[0] = 5;
	iarr[1] = 5;

	// Get memory address and insert double into the int array
	double *dp = &iarr[0];
	*dp = 7.5;

	// Free the memory
	free(iarr);

	return 0;
}
