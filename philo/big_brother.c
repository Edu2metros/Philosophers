/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:28:27 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 15:35:14 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo, t_data *data)
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
		print_instance(data, philo->philo_id, DIE);
		pthread_mutex_lock(&data->died);
		data->flag_die = 1;
		pthread_mutex_unlock(&philo->time_eat);
		pthread_mutex_unlock(&data->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->time_eat);
	return (0);
}

static void	check_meals(t_philo *philo, t_data *data)
{
	static int	i;
	int			id;

	id = 0;
	while (id < data->number_philos)
	{
		pthread_mutex_lock(&philo[id].size_eat);
		pthread_mutex_lock(&philo[id].full);
		if (philo[id].count_eat >= data->number_philos_eat
			&& philo[id].flag_full == 0)
		{
			philo[id].flag_full = 1;
			i++;
		}
		pthread_mutex_unlock(&philo[id].size_eat);
		pthread_mutex_unlock(&philo[id].full);
		id++;
	}
	if (i == data->number_philos)
	{
		pthread_mutex_lock(&data->died);
		data->flag_die = 1;
		pthread_mutex_unlock(&data->died);
	}
}

void	*big_brother(void *arg)
{
	t_data	*data;
	int		id;

	data = (t_data *)arg;
	if (data->number_philos == 1)
		return (NULL);
	while (1)
	{
		id = 0;
		while (id < data->number_philos)
		{
			if (philo_dead(&data->philo[id], data))
				return (NULL);
			if (data->number_philos_eat != -1)
				check_meals(data->philo, data);
			id++;
		}
	}
	return (NULL);
}
