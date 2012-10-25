/******************************************************************************
   main.c

   Implementation of a simple FIFO buffer as a linked list defined in list.h.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

int main(int argc, char* argv[])
{
    // FIFO list;
	List *fifo = list_new();

    list_add(fifo, node_new_str("s1"));
    list_add(fifo, node_new_str("s2"));

    Node *n1 = list_remove(fifo);
    if (n1 == NULL) { printf("Error no elements in list\n"); exit(-1);}
    Node *n2 = list_remove(fifo);
    if (n2 == NULL) { printf("Error no elements in list\n"); exit(-1);}

    char *n1elm = (char *)n1->elm;
    char *n2elm = (char *)n2->elm;

    printf("%s\n%s\n", n1elm, n2elm);

	return 0;
}