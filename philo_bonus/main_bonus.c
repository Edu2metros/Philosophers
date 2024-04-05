/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:11:25 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 17:23:06 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long get_time(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result);
}

void print_instance(t_data *data, int id, char *str)
{
	long	time;

	time = get_time() - data->time_init;
	printf("%ld %d %s\n", time, id, str);
}

int	current_status_philo(t_data *data)
{
	int	result;

	result = data->flag_die;
	return (result);
}

void init_fork_philo(t_data *data)
{
	int i;
	i = 0;
	while(i < data->number_philos)
		data->philo[i++].pid = fork();
}

void grab_forks(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	print_instance(data, philo->id, "has taken a fork");

}

void philo_eat(t_philo *philo, t_data *data)
{
	grab_forks(philo, data);
	print_instance(data, philo->id, "is eating");
	usleep(data->time_eat * 1000);
	//monitor
}

void philo_sleep_n_think(t_philo *philo, t_data *data)
{
	//sleep
}


void rotine_philo(t_philo *philo, t_data *data)
{
	while (1)
	{
		philo_eat(philo, data);
		//sleep
		//think
		//die
	}
}

void child_process(t_data *data)
{
	int i;
	i = 0;
	while (i < data->number_philos)
	{
		if (data->philo[i].pid == 0)
			rotine_philo(&data->philo[i], data);
		i++;
	}

}

void father_process(t_data *data)
{
	int i;
	i = 0;
	while (i < data->number_philos)
	{
		waitpid(data->philo[i].pid, NULL, 0);
		i++;
	}
}

void philo_process(t_data *data)
{
	child_process(data);
	father_process(data);
}

static	philosophers(char **argv)
{
	t_data	*data;

	data = init(argv);
	init_fork_philo(data);
	philo_process(data);
	//finish
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	philosophers(argv);
	return (EXIT_SUCCESS);
}
