/******************************************************************************
   main.c

   Implementation of a simple FIFO buffer as a linked list defined in list.h.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "test.h"

int main(int argc, char* argv[])
{
	// Tests if the list even works.
	nonThreadTest();

	// Tests how the list works with multiple threads.
	threadTest();

	return 0;
}