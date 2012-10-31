#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

List *fifo;
int number_of_elements_per_thread;

// The code for the threads.
void *TaskCode(void *argument)
{
    // Converts the parameter to an integer that holds the number
    // of the thread.
    int *threadNo = (int *) argument;

    int i;
    // Adds elements to the list.
    for (i = 0; i < number_of_elements_per_thread; ++i)
    {
        char x[250];
        char *s = "Thread";
        sprintf(x, "%s #%d, element %d", s, *threadNo + 1, i);
        list_add(fifo, node_new_str(x));
    }

    // Removes elements from the list.
    for (i = 0; i < number_of_elements_per_thread; ++i)
    {
        Node *node = list_remove(fifo);
        char *nodeElem = (char *)node->elm;
        printf("%s\n", nodeElem);
    }

    pthread_exit(0);
}

// Method for testing that the list works with threads.
int main(int argc, char* argv[])
{
    int rc, i;
    int number_of_threads = atoi(argv[3]);
    number_of_elements_per_thread = atoi(argv[2]);
    fifo = list_new();
    pthread_t threads[number_of_threads];

    // Creates all the threads and makes them do what they are supposed to.
    for (i=0; i<number_of_threads; ++i) 
    {
        rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &i);
        assert(0 == rc);
    }
  
    // Wait for all threads to finish
    for (i=0; i<number_of_threads; ++i) 
    {
        rc = pthread_join(threads[i], NULL);
        assert(0 == rc);
    }

    return 0;
}
