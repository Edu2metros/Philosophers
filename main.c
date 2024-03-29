/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:37:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:34:09 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo(void)
{
	static t_philo	philo;

	return (&philo);
}

void	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

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

#include <sys/time.h>

int	big_brother_check(struct timeval old_time, int philo_id)
{
	struct timeval	current_time;
	long			elapsed_time_in_microseconds;

	pthread_mutex_lock(&philo()->mutex);
	gettimeofday(&current_time, NULL);
	elapsed_time_in_microseconds = (current_time.tv_sec - old_time.tv_sec)
		* 1000000 + (current_time.tv_usec - old_time.tv_usec);
	if (elapsed_time_in_microseconds < philo()->time_die )
		philo()->died = 1;
	pthread_mutex_unlock(&philo()->mutex);
	return (philo()->died);
}

void	NAOSEI(void *arg)
{
	int				*thread_id;
	int				philo_id;
	int				*forks;
	int				left_fork;
	int				right_fork;
	struct timeval	current_time;

	thread_id = (int *)arg;
	philo_id = *thread_id;
	forks = philo()->forks;
	left_fork = philo_id;
	right_fork = (philo_id + 1) % philo()->number_philo;
	gettimeofday(&current_time, NULL);
	while (1)
	{
		pthread_mutex_lock(&philo()->mutex);
        if(philo()->number_philo == 1)
        {
            printf("%d has taken a fork\n");
            pthread_mutex_unlock(&philo()->mutex);
            printf("MORREU TROXA\n");
            philo()->died = 1;
            break ;
        }
		if (forks[left_fork] == 0 && forks[right_fork] == 0
			&& left_fork != right_fork)
		{
			forks[left_fork] = 1;
			forks[right_fork] = 1;
			printf("%d has taken a fork\n", philo_id);
			pthread_mutex_unlock(&philo()->mutex);
			gettimeofday(&current_time, NULL);
			printf("%d is eating\n", philo_id);
			usleep(philo()->time_eat * 1000);
			pthread_mutex_lock(&philo()->mutex);
			forks[left_fork] = 0;
			forks[right_fork] = 0;
			pthread_mutex_unlock(&philo()->mutex);
			printf("%d is sleeping\n", philo_id);
			usleep(philo()->time_sleep * 1000);
		}
		else
		{
			pthread_mutex_unlock(&philo()->mutex);
			usleep(100);
		}
		if (!big_brother_check(current_time, philo_id))
		{
			printf("%d MMORREU AHHAHA\n", philo_id);
			break ;
		}
	}
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
		pthread_create(&thread[i], NULL, NAOSEI, &thread_id[i]);
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
	check_args(argc, argv);
	init(argv);
	philosophers();
	free(philo()->forks);
	return (EXIT_SUCCESS);
}
