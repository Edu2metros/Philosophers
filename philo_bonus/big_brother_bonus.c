/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:13:36 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 18:37:30 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void die(t_philo *philo, t_data *data)
{
    long die;
    die = get_time() - philo->last_time_eat;
    if(die >= data->time_die)
    {
        print_instance(data, philo->id, "died");
        exit(EXIT_FAILURE);
    }
}

static void check_eat(t_philo *philo, t_data *data)
{
    if(philo->count_eat >= data->number_philos_eat && philo->flag_full == 0)
    {
        philo->flag_full = 1;
        data->flag_eat_enough++;
    }
    if(data->flag_eat_enough == data->number_philos)
    {
        data->flag_die = 1;
        exit(EXIT_FAILURE);
    }
}

void big_brother(t_philo *philo, t_data *data)
{
    die(philo, data);
    check_eat(philo, data);
}

