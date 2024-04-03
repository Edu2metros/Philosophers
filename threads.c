/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:38:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/02 18:03:12 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time() {
    struct timeval current_time;
    long milliseconds;

    gettimeofday(&current_time, NULL);
    milliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return milliseconds;
}

int	philo_dead(t_thread *thread)
{
	long time_die;
	
	pthread_mutex_lock(&philo()->mutex);
	time_die = get_time() - thread->eat_time;
	if(thread->philo_id == 0)
		printf("ULTIMA VEZ QUE COMEU: %ld\n", thread->eat_time);
	if (philo()->time_die < time_die)
	{
		printf("\x1b[31m%ld %d MORREU\x1b[0m\n", time_die, thread->philo_id + 1);
		printf("TEMPO DE MORRER: %ld\n", time_die);
		printf("PHILO ID %d\n", thread->philo_id);
		printf("ULTIMA VEZ QUE COMEU TEMPO: %ld\n", thread->eat_time);
		printf("ULTIMA VEZ COMER TEMPO CALCULADO: %ld\n", get_time());
		philo()->died = 1;
		pthread_mutex_unlock(&philo()->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo()->mutex);
	return (0);
}

int	big_brother(void)
{
	int			id;
	int			total_philo;
	t_thread	*thread;

	thread = philo()->thread;
	total_philo = philo()->number_philo;
	if (philo()->number_philo == 1)
		return (0);
	while (1)
	{
		usleep(100);
		id = 0;
		while (id <= total_philo)
		{
			if (philo_dead(&thread[id]))
				return (0);
			id++;
		}
	}
}

int	one_philo(int philo_id)
{
	long	time;

	time = philo()->time - get_time();
	if (philo()->number_philo == 1)
	{
		printf("%d has taken a fork\n", philo_id);
		pthread_mutex_unlock(&philo()->mutex);
		printf("\x1b[31m%ld %d MORREU SOZINHO TROXA\x1b[0m\n", time, philo_id
			+ 1);
		philo()->died = 1;
	}
	return (philo()->died);
}

void	time_eat(int philo_id)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	philo()->thread[philo_id].eat_time = get_time();
}

void	print_instance(int philo_id, char *str)
{
	long	time;

	if (philo()->died == 1)
		return ;
	time = get_time() - philo()->time;
	printf("%ld %d %s\n", time, philo_id + 1, str);
}

int	philo_eat(int philo_id)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo_id;
	right_fork = (philo_id + 1) % philo()->number_philo;
	if (philo_id % 2 == 0)
		usleep(300);
	pthread_mutex_lock(&philo()->fork_mx[left_fork]);
	pthread_mutex_lock(&philo()->fork_mx[right_fork]);
	if (philo()->forks[left_fork] == 0 && philo()->forks[right_fork] == 0)
	{
		philo()->forks[left_fork] = 1;
		philo()->forks[right_fork] = 1;
		print_instance(philo_id, "has taken a fork");
		pthread_mutex_unlock(&philo()->fork_mx[right_fork]);
		pthread_mutex_unlock(&philo()->fork_mx[left_fork]);
		print_instance(philo_id, "is eating");
		philo()->thread[philo_id].eat_time = get_time();
		// printf("ULTIMA VEZ QUE COMEU TEMPO: %ld\n",
			// philo()->thread[philo_id].eat_time);
		usleep(philo()->time_eat * 1000);
		pthread_mutex_lock(&philo()->fork_mx[left_fork]);
		pthread_mutex_lock(&philo()->fork_mx[right_fork]);
		philo()->forks[left_fork] = 0;
		philo()->forks[right_fork] = 0;
		pthread_mutex_unlock(&philo()->fork_mx[right_fork]);
		pthread_mutex_unlock(&philo()->fork_mx[left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo()->fork_mx[right_fork]);
	pthread_mutex_unlock(&philo()->fork_mx[left_fork]);
	return (0);
}

void	philo_sleep_n_think(int philo_id)
{
	if (philo()->died == 1)
		return ;
	print_instance(philo_id, "is sleeping");
	usleep(philo()->time_sleep * 1000);
	print_instance(philo_id, "is thinking");
}

void	*threads(void *arg)
{
	int	philo_id;

	philo_id = *(int *)arg;
	while (philo()->died == 0)
	{
		if (philo_id % 2 == 0)
			usleep(5);
		pthread_mutex_lock(&philo()->mutex);
		if (philo()->died != 0)
		{
			pthread_mutex_unlock(&philo()->mutex);
			break ;
		}
		if (philo_eat(philo_id))
		{
			pthread_mutex_unlock(&philo()->mutex);
			philo_sleep_n_think(philo_id);
		}
		else
		{
			pthread_mutex_unlock(&philo()->mutex);
			usleep(100);
		}
	}
	return (NULL);
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
