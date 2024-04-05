/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:23:50 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 14:51:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_mutex_eat(t_data *data, int right_fork, int left_fork, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&data->fork_m[right_fork]);
		pthread_mutex_lock(&data->fork_m[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&data->fork_m[left_fork]);
		pthread_mutex_lock(&data->fork_m[right_fork]);
	}
}

void	unlock_mutex_eat(t_data *data, int right_fork, int left_fork, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&data->fork_m[right_fork]);
		pthread_mutex_unlock(&data->fork_m[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork_m[left_fork]);
		pthread_mutex_unlock(&data->fork_m[right_fork]);
	}
}

void	philo_eat(t_data *data, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	right_fork = (id + 1) % data->number_philos;
	lock_mutex_eat(data, right_fork, left_fork, id);
	print_instance(data, id, "has taken a fork");
	pthread_mutex_lock(&data->philo[id].time_eat);
	data->philo[id].last_time_eat = get_time();
	pthread_mutex_unlock(&data->philo[id].time_eat);
	print_instance(data, id, "is eating");
	usleep(data->time_eat * 1000);
	add_eat(&data->philo[id]);
	unlock_mutex_eat(data, right_fork, left_fork, id);
}

void	philo_sleep_n_think(t_data *data, int id)
{
	print_instance(data, id, "is sleeping");
	usleep(data->time_sleep * 1000);
	print_instance(data, id, "is thinking");
}

void	*routine(void *arg)
{
	int		id;
	t_data	*data;

	id = *(int *)arg;
	data = *control_struct();
	if (data->number_philos == 1)
		return (NULL);
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
