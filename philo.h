/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:49:35 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/02 14:48:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_thread
{
	int				philo_id;
	int				eat;
	long			eat_time;
}					t_thread;

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*fork_mx;
	t_thread		*thread;
	long			time;
	int				number_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_philo_must_eat;
	int				*forks;
	int				died;
}					t_philo;

t_philo				*philo(void);

int					ft_atoi(const char *str);
int					is_all_digit(char **argv);
void				print_stderror(void);
int					ft_isdigit(char c);
int					check_args(int argc, char **argv);
int					big_brother(void);
void				*threads(void *arg);

#endif