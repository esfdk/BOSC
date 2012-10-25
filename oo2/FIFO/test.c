#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "test.h"

List *fifo;
int start_number_of_elements = 5;

void nonThreadTest()
{
    printf("----------\nStart of test without threads.\n");

    // FIFO list;
    fifo = list_new();

    list_add(fifo, node_new_str("s1"));
    list_add(fifo, node_new_str("s2"));

    Node *n1 = list_remove(fifo);
    if (n1 == NULL) { printf("Error no elements in list\n"); exit(-1);}
    Node *n2 = list_remove(fifo);
    if (n2 == NULL) { printf("Error no elements in list\n"); exit(-1);}
    printf("%s\n%s\n", n1->elm, n2->elm);
    printf("----------\n");
}

void threadTest()
{
    printf("----------\nStart of test with threads.\n");

    int number_of_threads = 3;
    pthread_t threads[number_of_threads];

    fifo = list_new();
    
    int rc, i;

    rc = pthread_create(&threads[0], NULL, threadOne, NULL);
    rc = pthread_create(&threads[1], NULL, threadTwo, NULL);
    rc = pthread_create(&threads[2], NULL, threadThree, NULL);
    
    /* wait for all threads to complete */
    for (i=0; i<number_of_threads; ++i) {
        rc = pthread_join(threads[i], NULL);
        assert(0 == rc);
    }

    printf("----------\n");

    exit(EXIT_SUCCESS);
}

void *threadOne(void *argument)
{
    int i;
    for (i = 0; i < start_number_of_elements; ++i)
    {
        char x[100];
        char *s = "Thread A";
        sprintf(x, "%s %d", s, i);
        list_add(fifo, node_new_str(x));
        int n;
        n=random() % 100;  /* n is random number in range of 0 - 99 */
        //sleep(n / 10);
    }//

    for (i = 0; i < start_number_of_elements; ++i)
    {
        Node *node = list_remove(fifo);
        printf("%s\n", node->elm);
    }

    pthread_exit(0);
}

void *threadTwo(void *argument)
{
    int i;
    for (i = 0; i < start_number_of_elements; ++i)
    {
        char x[100];
        char *s = "Thread B";
        sprintf(x, "%s %d", s, i);
        list_add(fifo, node_new_str(x));
        int n;
        n=random() % 100;  /* n is random number in range of 0 - 99 */
//        sleep(n / 10);
    }

    for (i = 0; i < start_number_of_elements; ++i)
    {
        Node *node = list_remove(fifo);
        printf("%s\n", node->elm);
    }

    pthread_exit(0);
}

void *threadThree(void *argument)
{
    int i;
    for (i = 0; i < start_number_of_elements; ++i)
    {
        char x[100];
        char *s = "Thread C";
        sprintf(x, "%s %d", s, i);
        list_add(fifo, node_new_str(x));
        int n;
        n=random() % 100;  /* n is random number in range of 0 - 99 */
//        sleep(n / 10);
    }

    for (i = 0; i < start_number_of_elements; ++i)
    {
        Node *node = list_remove(fifo);
        printf("%s\n", node->elm);
    }

    pthread_exit(0);
}