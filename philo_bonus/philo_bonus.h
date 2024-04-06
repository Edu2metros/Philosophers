/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:07:58 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 18:35:54 by eddos-sa         ###   ########.fr       */
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
	int		flag_eat_enough;
	t_philo	*philo;
}			t_data;

void big_brother(t_philo *philo, t_data *data);
int	check_args(int argc, char **argv);
t_data	*init(char **argv);
void init_fork_philo(t_data *data);
void philosophers(char **argv);
void rotine_philo(t_philo *philo, t_data *data);
void grab_forks(t_philo *philo, t_data *data);
void drop_forks(t_data *data);
void wait_and_check(t_data *data, long wait);
long get_time(void);
void print_instance(t_data *data, int id, char *str);
int	current_status_philo(t_data *data);
int	ft_atoi(const char *str);

#endif