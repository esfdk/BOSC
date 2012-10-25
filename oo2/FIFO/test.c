#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

List *fifo;
int number_of_elements_per_thread;


void *TaskCode(void *argument)
{
    int *threadNo = (int *) argument;

    int i;
    for (i = 0; i < number_of_elements_per_thread; ++i)
    {
        char x[250];
        char *s = "Thread";
        sprintf(x, "%s #%d, element %d", s, *threadNo, i);
        list_add(fifo, node_new_str(x));
    }

    for (i = 0; i < number_of_elements_per_thread; ++i)
    {
        Node *node = list_remove(fifo);
        char *nodeElem = (char *)node->elm;
        printf("%s\n", nodeElem);
    }

    pthread_exit(0);
}

int main(int argc, char* argv[])
{
    int rc, i;
    int number_of_threads = atoi(argv[3]);
    number_of_elements_per_thread = atoi(argv[2]);
    fifo = list_new();
    pthread_t threads[number_of_threads];

    /* create all threads */
    for (i=0; i<number_of_threads; ++i) 
    {
        rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &number_of_threads);
        assert(0 == rc);
    }
    
    printf("dawd\n");
  
    /* wait for all threads to complete */
    for (i=0; i<number_of_threads; ++i) 
    {
        rc = pthread_join(threads[i], NULL);
        assert(0 == rc);
    }

    return 0;
}