/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:59:07 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 13:59:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos
{
	pthread_mutex_t	time_eat;
	pthread_mutex_t	size_eat;
	pthread_mutex_t	full;
	int				flag_full;
	long			last_time_eat;
	int				count_eat;
	int				philo_id;
}					t_philo;

typedef struct s_data
{
	int				number_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_philos_eat;
	int				flag_die;
	int				*forks;
	int				id;
	long			time_init;
	t_philo			*philo;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	died;
}					t_data;

void				*big_brother(void *arg);
int					check_args(int argc, char **argv);
void				finish(t_data *data, pthread_t *thread_id);
t_data				*init(char **argv);
void				handle_one_philo(t_data *data);
void				add_eat(t_philo *philo);
int					current_status_philo(t_data *data);
void				philo_eat(t_data *data, int id);
void				philo_sleep_n_think(t_data *data, int id);
void				*routine(void *arg);
long				get_time(void);
t_data				**control_struct(void);
void				print_instance(t_data *data, int id, char *msg);
int					ft_atoi(const char *str);

#endif