#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "List/list.h"

// Header
void producer(void*);
void consumer(void*);
Node *produceProduct();

// List
List *itemList; // The product buffer.

// Locks
pthread_mutex_t produce_lock; // Lock for produced_products.
pthread_mutex_t consume_lock; // Lock for consumed_products.

// Semaphores
sem_t empty; // Number of empty slots in the buffer.
sem_t full; // Number of filled slots in the buffer.
sem_t products_remaining; // Number of products still to be produced.

// Consumer and producer variables
int number_of_producers; // Number of product producers.
int number_of_consumers; // Number of product consumers.

// Product variables
int total_number_of_products; // Number of products to be produced in total.
int produced_products = 0; // Number of produced products.
int consumed_products = 0; // Number of consumed products.

// Buffer size
int buffer_size;

int main(int argc, char* argv[])
{
	// Initialise variables from input arguments
	number_of_producers = atoi(argv[2]);
	number_of_consumers = atoi(argv[3]);
	total_number_of_products = atoi(argv[5]);
	buffer_size = atoi(argv[4]);
	// Initialise semaphores
	if(sem_init(&empty, 0, buffer_size) != 0)
	{
		printf("\n Failed to initialise empty semaphore\n");
	}
	if(sem_init(&full, 0, 0) != 0)
	{
		printf("\n Failed to initialise full semaphore\n");
	}
	if(sem_init(&products_remaining, 0, total_number_of_products) != 0)
	{
		printf("\n Failed to initialise total_number_of_products semaphore\n");
	}
	
	// Initialise list
	itemList = list_new();
	
	// Initialise locks
	if (pthread_mutex_init(&produce_lock, NULL) != 0)
    {
        printf("\n Failed to initialise produce_lock\n");
    }
	
	if (pthread_mutex_init(&consume_lock, NULL) != 0)
    {
        printf("\n Failed to initialise consumed_lock\n");
    }
	
	// Consumer and producer thread arrays
	pthread_t consumer_thread_ids[number_of_consumers];
	pthread_t producer_thread_ids[number_of_producers];
	
	// Create threads
	int tn;
	for (tn = 0; tn < number_of_consumers; tn++){
        if(pthread_create(&consumer_thread_ids[tn], NULL, &consumer, (void*) tn))
		{
        	printf("Failed to create consumer number %d \n", tn);
        }
    }
	for (tn = 0; tn < number_of_producers; tn++){
        if(pthread_create(&producer_thread_ids[tn], NULL, &producer, (void*) tn))
		{
        	printf("Failed to create producer number %d \n", tn);
        }
    }
	
	// Join threads
	for (tn = 0; tn < number_of_consumers; tn++)
	{
    	pthread_join(consumer_thread_ids[tn], NULL);
    }
	for (tn = 0; tn < number_of_producers; tn++)
	{
    	pthread_join(producer_thread_ids[tn], NULL);
    }
	
	return 0;
}

// Producer code
void producer(void *argument)
{
	int *prodNo = (int *) argument;
	Node *node;
	
	while(1)
	{
		// Produce or stop
		int tw = sem_trywait(&products_remaining);
		if(tw == -1) // If there are no more products to be produced, end thread.
		{
			pthread_exit(0);
		}
		else if(tw == 0) // There are more products be produced.
		{	
			 node = produceProduct(); // Final product
		}
		else
		{
			printf("Some error occured when trying to wait on products_remaining semaphore");
		}
		
		// Add product to buffer
		sem_wait(&empty); // Wait for room in buffer.
		list_add(itemList, node); // Add node to list.
		sem_post(&full); // Signal full so buffer space is decreased by 1.
		
		int *products_in_buffer;
		sem_getvalue(full, *products_in_buffer);
		printf("Consumer %d consumed %s. Items in buffer: %d (out of %d", *prodNo, node->elm, *products_in_buffer, buffer_size);
		
		// Sleep for random time - between 0-9 seconds.
		sleep((random() % 100) / 10);
	}
}

// Consumer code
void consumer(void *argument)
{
	int *consNo = (int *) argument;
	Node *node;
	while(1){
		pthread_mutex_lock(&consume_lock); // Lock consumed_products.
		if(consumed_products == total_number_of_products) // If we have consumed all products, exit thread.
		{
			pthread_mutex_unlock(&consume_lock); // Release lock on consumed_products.
			pthread_exit(0); // Exit thread.
		}
		
		sem_wait(&full); // Wait for a product to exist in the buffer.
		
		node = list_remove(itemList); // Remove product from buffer.
		consumed_products++; // Increase amount of consumed products
		
		pthread_mutex_unlock(&consume_lock); // Unlock consumed_products.
		sem_post(&empty); // Signal empty so buffer space is increased by 1.
		
		int *products_in_buffer;
		sem_getvalue(full, *products_in_buffer);
		printf("Consumer %d consumed %s. Items in buffer: %d (out of %d", *consNo, node->elm, *products_in_buffer, buffer_size);
		
		sleep((random() % 100) / 10);
	}
}

// Produces a new node.
Node *produceProduct()
{
	Node* node;
	
	// Lock produced_products
	pthread_mutex_lock(&produce_lock);

	// Create node
	char tmp[250];
	sprintf(tmp, "ITEM_%d", produced_products);
	
	produced_products++; // Increased produced products.

	pthread_mutex_unlock(&produce_lock); // Unlocked produced_products.
	
	node = node_new_str(tmp); // Initialisation of the new node.
	
	return node;
}
