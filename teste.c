#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int				i = 0;
pthread_mutex_t	mutex;

void	*increment(void *arg)
{
	int	tid;

	tid = *(int *)arg;
	for (int j = 0; j < 5000; j++)
	{
		pthread_mutex_lock(&mutex);
		i++;
		printf("Thread %d\n", tid);
		printf("count j: %d\n", j);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	thread[2];
	int			thread_id[2];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 2; i++)
	{ // Corrija o loop principal
		thread_id[i] = i;
		pthread_create(&thread[i], NULL, increment, &thread_id[i]);
			// Corrija a passagem de argumentos
	}
	for (int i = 0; i < 2; i++)
	{ // Espere pela conclusão das threads
		pthread_join(thread[i], NULL);
	}
	pthread_mutex_destroy(&mutex); // Destrua o mutex após o uso
	return (0);
}
