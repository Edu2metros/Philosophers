#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philos
{
	pthread_mutex_t time_eat;
	long			last_time_eat;
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

int					ft_atoi(const char *str);
int					is_all_digit(char **argv);
int					negative_numbers(char **argv);
void				print_stderror(void);
int					check_args(int argc, char **argv);
long				get_time(void);
t_data				**control_struct(void);
void				print_instance(t_data *data, int id, char *msg);
void				fill_info_data(t_data *data, char **argv);
t_data				*init(char **argv);
void				init_philo_struct(t_data *data);
void				forks_init(t_data *data);
void time_eat_init(t_philo *philo, int total_philos);

#endif