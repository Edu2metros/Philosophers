/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:07:58 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 17:13:03 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_philos
{
	pid_t	pid;
	int		flag_full;
	long	last_time_eat;
	int		count_eat;
	int		id;
}			t_philo;

typedef struct s_data
{
	int		number_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		number_philos_eat;
	int		flag_die;
	sem_t	*forks;
	int		id;
	long	time_init;
	t_philo	*philo;
}			t_data;

int			check_args(int argc, char **argv);
t_data		*init(char **argv);

#endif