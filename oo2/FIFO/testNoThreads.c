/******************************************************************************

testNoThreads.c

Testign that the FIFO list actually works as we want it to.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

int main(int argc, char* argv[])
{
    // Creates a FIFO list;
    List *fifo = list_new();

    // Adds two elements to the list.
    list_add(fifo, node_new_str("s1"));
    list_add(fifo, node_new_str("s2"));

    // Removes the first element from the list and checks that is it not null
    Node *n1 = list_remove(fifo);
    if (n1 == NULL) { printf("Error no elements in list\n"); exit(-1);}
    // Removes the second element from the list and checks that is it not null
    Node *n2 = list_remove(fifo);
    if (n2 == NULL) { printf("Error no elements in list\n"); exit(-1);}

    // Saves the elm of the two nodes as strings.
    char *n1elm = (char *)n1->elm;
    char *n2elm = (char *)n2->elm;

    // Prints the two elements.
    printf("%s\n%s\n", n1elm, n2elm);

    return 0;
}