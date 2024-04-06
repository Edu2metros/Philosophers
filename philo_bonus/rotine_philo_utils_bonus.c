/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_philo_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:15:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 18:43:50 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void grab_forks(t_philo *philo, t_data *data)
{
    printf("entrou1\n");
	sem_wait(data->forks);
    printf("entrou2\n");
	sem_wait(data->forks);
	print_instance(data, philo->id, "has taken a fork");
}

void drop_forks(t_data *data)
{
    sem_post(data->forks);
    sem_post(data->forks);
}

void wait_and_check(t_data *data, long wait)
{
    long total;
    total = get_time();
    while(get_time() - total < wait)
    {
        big_brother(data->philo, data);
        usleep(10);
    }
}
