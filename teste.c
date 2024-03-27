#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5
#define ITERATIONS 10000

int				shared_counter = 0;
pthread_mutex_t	mutex;

void	*increment_counter(void *thread_id)
{
	int	tid;

	tid = *(int *)thread_id;
	for (int i = 0; i < ITERATIONS; ++i)
	{
		pthread_mutex_lock(&mutex);
			// Lock the mutex before accessing shared_counter
		shared_counter++;
		printf("Thread %d: Incremented counter to %d\n", tid, shared_counter);
		pthread_mutex_unlock(&mutex);
			// Unlock the mutex after accessing shared_counter
	}
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM_THREADS];
	int			thread_ids[NUM_THREADS];

	// Initialize mutex
	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		return (1);
	}
	// Create threads
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		thread_ids[i] = i;
		if (pthread_create(&threads[i], NULL, increment_counter,
				(void *)&thread_ids[i]) != 0)
		{
			printf("Thread creation failed\n");
			return (1);
		}
	}
	// Wait for threads to finish
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	// Destroy mutex
	pthread_mutex_destroy(&mutex);
	printf("Final counter value: %d\n", shared_counter);
	return (0);
}
