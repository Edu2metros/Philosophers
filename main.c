/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:37:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/02 18:08:03 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_philo)
	{
		philo->forks[i] = 0;
		i++;
	}
}

void setup_time(t_philo *philo)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    philo->time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void setup_mutex(t_philo *philo)
{
	int i;
	
	i = 0;
	philo->fork_mx = malloc(sizeof(pthread_mutex_t) * philo->number_philo);
	
	while (i < philo->number_philo)
	{
		pthread_mutex_init(&philo->fork_mx[i], NULL);
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
	pthread_mutex_init(&philo()->mutex, NULL);
	setup_forks(philo());
	setup_time(philo());
	setup_mutex(philo());
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Erro: malloc falhou\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void setup_eat(t_thread *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo()->number_philo)
	{
		philo_struct[i].eat = 0;
		philo_struct[i].philo_id = i;
		i++;
	}
	philo()->thread = philo_struct;
}

void	philosophers(void)
{
	pthread_t	*thread;
	t_thread	*philo_struct;
	int			*thread_id;
	int			i;
	int			j;

	thread = malloc(philo()->number_philo * sizeof(pthread_t));
	thread_id = malloc(philo()->number_philo * sizeof(int));
	philo_struct = malloc(philo()->number_philo * sizeof(t_thread));
	setup_eat(philo_struct);
	i = 0;
	while (i < philo()->number_philo && philo()->died != 1)
	{
		thread_id[i] = i;
		pthread_create(&thread[i], NULL, threads, &thread_id[i]);
		i++;
	}
	big_brother();
	j = 0;
	while (j < philo()->number_philo)
	{
		pthread_join(thread[j], NULL);
		j++;
	}
	free(thread);
	free(thread_id);
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
