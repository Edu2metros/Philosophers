/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:49:35 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/30 16:38:14 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	t_thread		*thread;
	int				number_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_philo_must_eat;
	int				*forks;
	int				died;
}					t_philo;

typedef struct s_thread
{
	int				philo_id;
	int				eat;
	struct timeval	old_time;
}					t_thread;

t_philo				*philo(void);

int					ft_atoi(const char *str);
int					is_all_digit(char **argv);
void				print_stderror(void);
int					ft_isdigit(char c);
int					check_args(int argc, char **argv);

int					big_brother_check(struct timeval old_time, int philo_id);
void				threads(void *arg);

#endif