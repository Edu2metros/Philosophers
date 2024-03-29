/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:49:35 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:21:07 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>	

typedef struct s_philo
{
	pthread_mutex_t mutex;
	int number_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int number_philo_must_eat;
	int *forks;
	int died;
}	t_philo;


int	ft_atoi(const char *str);

#endif