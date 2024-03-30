/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:38:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/30 13:51:10 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	big_brother_check(struct timeval old_time, int philo_id)
{
	struct timeval	current_time;
	long			elapsed_time_in_microseconds;

	pthread_mutex_lock(&philo()->mutex);
	gettimeofday(&current_time, NULL);
	elapsed_time_in_microseconds = (current_time.tv_sec - old_time.tv_sec)
		* 1000000 + (current_time.tv_usec - old_time.tv_usec);
	if (elapsed_time_in_microseconds < philo()->time_die)
		philo()->died = 1;
	pthread_mutex_unlock(&philo()->mutex);
	return (philo()->died);
}


void threads(void *arg)
{
    int *philo_id;
    
}

/* void	threads(void *arg)
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
		if (philo()->number_philo == 1)
		{
			printf("%d has taken a fork\n", philo_id);
			pthread_mutex_unlock(&philo()->mutex);
			printf("\x1b[31m%d MMORREU AHHAHA\x1b[0m\n", philo_id);
			philo()->died = 1;
			break ;
		}
		else if (forks[left_fork] == 0 && forks[right_fork] == 0
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
			printf("\x1b[31m%d MMORREU AHHAHA\x1b[0m\n", philo_id);
			break ;
		}
	}
} */
