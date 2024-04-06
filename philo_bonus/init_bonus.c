/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:20:32 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 17:21:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void init_fork_philo(t_data *data)
{
	int i;
	i = 0;
	while(i < data->number_philos)
		data->philo[i++].pid = fork();
}

static void	init_philo_struct(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	while (i < data->number_philos)
	{
		data->philo[i].id = i;
		data->philo[i].last_time_eat = 0;
		data->philo[i].count_eat = 0;
		data->philo[i].flag_full = 0;
		i++;
	}
}

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
	data->forks = sem_open("forks", O_CREAT , 0644, data->number_philos);
}

t_data	*init(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	fill_info_data(data, argv);
	init_philo_struct(data);
	return (data);
}
