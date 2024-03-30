/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:37:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/30 13:37:54 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_forks(void)
{
	int	i;

	i = 0;
	while (i < philo()->number_philo)
	{
		philo()->forks[i] = 0;
		i++;
	}
}

void	init(char **argv)
{
	int	i;

	i = 0;
	philo()->number_philo = ft_atoi(argv[1]);
	philo()->forks = malloc(sizeof(int) * philo()->number_philo);
	philo()->time_die = ft_atoi(argv[2]);
	philo()->time_eat = ft_atoi(argv[3]);
	philo()->time_sleep = ft_atoi(argv[4]);
	philo()->died = 0;
	if (argv[5] != NULL)
		philo()->number_philo_must_eat = ft_atoi(argv[5]);
	else
		philo()->number_philo_must_eat = -1;
	setup_forks();
}

void	philosophers(void)
{
	pthread_t	thread[philo()->number_philo];
	int			thread_id[philo()->number_philo];
	int			i;
	int			j;

	i = 0;
	j = 0;
	pthread_mutex_init(&philo()->mutex, NULL);
	while (i < philo()->number_philo && philo()->died != 1)
	{
		thread_id[i] = i;
		pthread_create(&thread[i], NULL, threads, &thread_id[i]);
		i++;
	}
	while (j < philo()->number_philo)
	{
		pthread_join(thread[j], NULL);
		j++;
	}
	pthread_mutex_destroy(&philo()->mutex);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	init(argv);
	philosophers();
	free(philo()->forks);
	return (EXIT_SUCCESS);
}
