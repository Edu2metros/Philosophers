/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:36:21 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 13:59:40 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_info_data(t_data *data, char **argv)
{
	data->number_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->number_philos_eat = ft_atoi(argv[5]);
	else
		data->number_philos_eat = -1;
	data->flag_die = 0;
	data->time_init = get_time();
}

static void	init_philo_struct(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	while (i < data->number_philos)
	{
		data->philo[i].philo_id = 0;
		data->philo[i].last_time_eat = 0;
		data->philo[i].count_eat = 0;
		data->philo[i].flag_full = 0;
		i++;
	}
}

static void	forks_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(int) * data->number_philos);
	while (i < data->number_philos)
		data->forks[i++] = 0;
	i = 0;
	data->fork_m = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	while (i < data->number_philos)
	{
		pthread_mutex_init(&data->fork_m[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->died, NULL);
}

static void	time_eat_init(t_philo *philo, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		pthread_mutex_init(&philo[i].time_eat, NULL);
		pthread_mutex_init(&philo[i].size_eat, NULL);
		pthread_mutex_init(&philo[i].full, NULL);
		i++;
	}
}

t_data	*init(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	fill_info_data(data, argv);
	init_philo_struct(data);
	forks_init(data);
	time_eat_init(data->philo, data->number_philos);
	*control_struct() = data;
	return (data);
}
