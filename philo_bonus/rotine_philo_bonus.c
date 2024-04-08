/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:22:00 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 13:06:14 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void philo_eat(t_philo *philo, t_data *data)
{
	grab_forks(philo, data);
	print_instance(data, philo->id, "is eating");
	philo->last_time_eat = get_time();
    wait_and_check(data, data->time_eat);
    philo->count_eat++;
    drop_forks(data);
}

static void philo_sleep_n_think(t_philo *philo, t_data *data)
{
    //Sleep
	print_instance(data, philo->id, "is sleeping");
    big_brother(philo, data);
    wait_and_check(data, data->time_sleep);
    //Think
    print_instance(data, philo->id, "is thinking");
    big_brother(philo, data);
    while (*((int *)data->forks) < 2)
        big_brother(philo, data);
}

void handle_one_philo(t_philo *philo, t_data *data)
{
    print_instance(data, philo->id, "has taken a fork");
    wait_and_check(data, data->time_die);
    print_instance(data, philo->id, DIE);
    exit_child(data, DIED);
}

void rotine_philo(t_philo *philo, t_data *data)
{
    if(data->number_philos == 1)
        handle_one_philo(philo, data);
    else
    {
        while (1)
        {
            philo_eat(philo, data);
            philo_sleep_n_think(philo, data);
        }
    }
}

