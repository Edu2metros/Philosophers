/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:24:34 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 14:17:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_data *data)
{
	print_instance(data, 0, "has taken a fork");
	usleep(data->time_die * 1000);
	print_instance(data, 0, "died");
	pthread_mutex_lock(&data->died);
	data->flag_die = 1;
	pthread_mutex_unlock(&data->died);
}

void	add_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->size_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->size_eat);
}

int	current_status_philo(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->died);
	result = data->flag_die;
	pthread_mutex_unlock(&data->died);
	return (result);
}
