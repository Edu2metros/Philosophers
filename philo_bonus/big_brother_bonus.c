/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:13:36 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 13:05:37 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void exit_child(t_data *data, int exit_status)
{
    sem_post(data->forks);
    sem_unlink("forks");
    sem_unlink("print");
    sem_close(data->forks);
    sem_close(data->print);
    free(data->philo);
    free(data);
    exit(exit_status);
}

static void die(t_philo *philo, t_data *data)
{
    long die;
    die = get_time() - philo->last_time_eat;
    if(die >= data->time_die)
    {
        print_instance(data, philo->id, DIE);
        exit_child(data, DIED);
    }
}

static void check_eat(t_philo *philo, t_data *data)
{
    if(data->number_philos_eat == -1)
        return ;
    if(philo->count_eat >= data->number_philos_eat)
        data->flag_eat_enough++;
    if(data->flag_eat_enough == data->number_philos)
        exit_child(data, EAT_ENOUGH);
}

void big_brother(t_philo *philo, t_data *data)
{
    if(philo->last_time_eat == 0)
        return ;
    die(philo, data);
    check_eat(philo, data);
}

