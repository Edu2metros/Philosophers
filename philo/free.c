/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:27:47 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 14:29:07 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_threads(t_data *data, pthread_t *thread_id)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
}

static void	destroy_all_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_mutex_destroy(&data->fork_m[i]);
		pthread_mutex_destroy(&data->philo[i].time_eat);
		pthread_mutex_destroy(&data->philo[i].size_eat);
		pthread_mutex_destroy(&data->philo[i].full);
		i++;
	}
}

static void	free_structs(t_data *data)
{
	free(data->philo);
	free(data->forks);
	free(data->fork_m);
	free(data);
}

void	finish(t_data *data, pthread_t *thread_id)
{
	wait_all_threads(data, thread_id);
	destroy_all_mutexes(data);
	free_structs(data);
}
