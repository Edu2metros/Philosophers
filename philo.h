/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:49:35 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/27 12:35:17 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <stdio.h>
#include <stdlib.h>


typedef struct s_philo
{
	int number_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int number_philo_must_eat;
}	t_philo;

int	ft_atoi(const char *str);

#endif