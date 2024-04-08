/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:07:58 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 13:17:46 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#define DIE "\033[1;31m💀 died 💀\033[0m"

#define DIED 1
#define EAT_ENOUGH 2

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
	sem_t 	*print;
	int		id;
	long	time_init;
	int		flag_eat_enough;
	t_philo	*philo;
}			t_data;

void big_brother(t_philo *philo, t_data *data);
int	check_args(int argc, char **argv);
t_data	*init(char **argv);
void philosophers(char **argv);
void rotine_philo(t_philo *philo, t_data *data);
void grab_forks(t_philo *philo, t_data *data);
void drop_forks(t_data *data);
void wait_and_check(t_data *data, long wait);
long get_time(void);
void print_instance(t_data *data, int id, char *str);
int	current_status_philo(t_data *data);
int	ft_atoi(const char *str);
void exit_child(t_data *data, int exit_status);

#endif