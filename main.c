#include "philo.h"

void	philo_eat(t_data *data, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	right_fork = (id + 1) % data->number_philos;
	print_instance(data, id, "has taken a fork");
	pthread_mutex_lock(&data->fork_m[left_fork]);
	pthread_mutex_lock(&data->fork_m[right_fork]);
	pthread_mutex_lock(&data->philo[id].time_eat);
	data->philo[id].last_time_eat = get_time();
	pthread_mutex_unlock(&data->philo[id].time_eat);
	print_instance(data, id, "is eating");
	usleep(data->time_eat * 1000);
	pthread_mutex_unlock(&data->fork_m[left_fork]);
	pthread_mutex_unlock(&data->fork_m[right_fork]);
}

void	philo_sleep_n_think(t_data *data, int id)
{
	print_instance(data, id, "is sleeping");
	usleep(data->time_sleep * 1000);
	print_instance(data, id, "is thinking");
}

int  current_status_philo(t_data *data)
{
	int result;

	pthread_mutex_lock(&data->died);
	result = data->flag_die;
	pthread_mutex_unlock(&data->died);
	return (result);
}

void	*routine(void *arg)
{
	int		id;
	t_data	*data;

	id = *(int *)arg;
	data = *control_struct();
	while (current_status_philo(data) == 0)
	{
		if (id % 2 == 0)
			usleep(300);
		if (current_status_philo(data) == 0)
			philo_eat(data, id);
		if (current_status_philo(data) == 0)
			philo_sleep_n_think(data, id);
	}
	return (NULL);
}

void	finish(t_data *data, pthread_t *thread_id)
{
	int i = 0;
	while (i < data->number_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->number_philos)
	{
		pthread_mutex_destroy(&data->fork_m[i]);
		pthread_mutex_destroy(&data->philo[i].time_eat);
		i++;
	}
	free(data->philo);
	free(data->forks);
	free(data->fork_m);
	free(data);
}
int	philo_dead(t_philo *philo, t_data *data)
{
	long	die;
	pthread_mutex_lock(&philo->time_eat);
	die = get_time() - philo->last_time_eat;
	if (philo->last_time_eat == 0)
	{
		pthread_mutex_unlock(&philo->time_eat);
		return (0);
	}
	if (die >= data->time_die)
	{
		print_instance(data, philo->philo_id, "died");
		pthread_mutex_lock(&data->died);
		data->flag_die 	= 1;
		pthread_mutex_unlock(&philo->time_eat);
		pthread_mutex_unlock(&data->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->time_eat);
	return (0);
}

void	*big_brother(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->number_philos == 1)
		return (NULL);
	while (1)
	{
		for (int id = 0; id < data->number_philos; id++)
		{
			if (philo_dead(&data->philo[id], data))
				return (NULL);
		}
	}
	return (NULL);
}

void init_threads(t_data *data)
{
	pthread_t thread_id[data->number_philos];
	pthread_t thread_big_brother;
	int philo_id[data->number_philos];
	int i;

	i = 0;
	pthread_create(&thread_big_brother, NULL, big_brother, data);
	while (i < data->number_philos)
	{
		philo_id[i] = i;
		pthread_create(&thread_id[i], NULL, routine, &philo_id[i]);
		i++;
	}
	pthread_join(thread_big_brother, NULL);
	finish(data, thread_id);
}


void	philosophers(char **argv)
{
	t_data	*data;

	data = init(argv);
	init_threads(data);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	philosophers(argv);
	return (EXIT_SUCCESS);
}